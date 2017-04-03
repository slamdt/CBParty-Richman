//
//  RichaManGameController.cpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/4/1.
//
//

#include "RichaManGameController.hpp"

SINGLETON_IMPL(RichManGameController)

bool RichManGameController::init() {
    mapNodes = CCArray::create();
    mapNodes->retain();
    mapSize = 10;
    tangshiLib[0u][0u] = "床前明月光";
    tangshiLib[0u][1] = "疑是地上霜";
    tangshiLib[1][0u] = "朝辞白帝彩云间";
    tangshiLib[1][1] = "千里江陵一日还";
    tangshiLib[2][0u] = "昔闻洞庭水";
    tangshiLib[2][1] = "今上岳阳楼";

    songciLib[0u][0u] = "昨夜雨疏风骤";
    songciLib[0u][1] = "浓睡不消残酒";
    songciLib[1][0u] = "问君能有几多愁";
    songciLib[1][1] = "恰似一江春水向东流";
    songciLib[2][0u] = "零落成泥碾作尘";
    songciLib[2][1] = "只有香如故";
    resetData();
    return true;
}

void RichManGameController::resetData() {
    mapNodes->removeAllObjects();
    player1 = NULL;
    player2 = NULL;
    endNode = NULL;
    player1Name = "";
    player2Name = "";
    curRound = -1;
    curTurn = -1;
    forwardBlocks = 0;
    gameModel = -1;
}

void RichManGameController::setGameModel(int model) {
    gameModel = model;
    if (gameModel == PLAY_WITH_NPC) {
        player2Name = "一只鸡";
    }
}

bool RichManGameController::getIsPlayWithNPC() {
    return gameModel == PLAY_WITH_NPC;
}

void RichManGameController::addMapNodes(RichManMapNode *node) {
    mapNodes->addObject(node);
}

void RichManGameController::setPlayer(RichManPlayer *_player, int playerId) {
    (playerId == PLAYER_1 ? player1 : player2) = _player;
}

void RichManGameController::setPlayerName(int editType, const char *playerName) {
    (editType == EDIT_SELF ? player1Name : player2Name) = playerName;
}

const char* RichManGameController::getPlayerName(int playerId) {
    return (playerId == PLAYER_1 ? player1Name : player2Name).c_str();
}

const char* RichManGameController::getTheOtherPlayerName(int playerId) {
    return (playerId == PLAYER_1 ? player2Name : player1Name).c_str();
}

bool RichManGameController::checkPlayerName() {
    if (strcmp(player1Name.c_str(), "") == 0 || strcmp(player2Name.c_str(), "") == 0) {
        return false;
    }
    return true;
}

RichManPlayer* RichManGameController::getCurPlayer() {
    return curTurn == PLAYER1_TURN ? player1 : player2;
}

void RichManGameController::gameStart() {
    curRound = 1;
    curTurn = PLAYER1_TURN;
    player1->turnToForward();
}

void RichManGameController::setForwardBlocks(int block) {
    forwardBlocks = block;
}

int RichManGameController::getCurPlayerScore() {
    return getCurPlayer()->getScore();
}

int RichManGameController::getCurPlayerId() {
    return getCurPlayer()->getPlayerId();
}

const char* RichManGameController::getCurPlayerName() {
    return getPlayerName(getCurPlayerId());
}

void RichManGameController::setCurPlayerScore(int scoreDelta) {
    getCurPlayer()->setScore(scoreDelta);
}

void RichManGameController::setRestRound(int restRounds) {
    getCurPlayer()->setRestRound(restRounds);
}

Json::Value& RichManGameController::setQuestion(int questionType) {
    Json::Value& targetLib = questionType == TANG_SHI ? tangshiLib : songciLib;
    int libSize = targetLib.size();
    int questionIndex = arc4random() % libSize;
    endNode->setHolderInfo(getCurPlayerId(), targetLib[questionIndex]);
    return targetLib[questionIndex];
}

bool RichManGameController::getCurPlayerIsNPC() {
    return getCurPlayer()->getIsNPC();
}

Json::Value& RichManGameController::getCurHolderInfo() {
    return endNode->getHolderInfo();
}

void RichManGameController::reduceHolderQuestions(int reduceSize) {
    endNode->reduceHolderQuestions(reduceSize);
}

void RichManGameController::grabHolder(int questionType) {
    endNode->clearHolderInfo();
    setQuestion(questionType);
}

void RichManGameController::freeHoldedBlock() {
    endNode->freeHoldedBlock();
}

void RichManGameController::answerWrong() {
    setCurPlayerScore(-30);
    int holderId = endNode->getHolderInfo()["playerId"].asInt();
    (holderId == PLAYER_1 ? player1 : player2)->setScore(30);
}

void RichManGameController::move() {
    RichManPlayer* movePlayer = getCurPlayer();
    int posxDelta = curTurn == PLAYER1_TURN ? -10 : 10;
    CCArray* aniArray = CCArray::create();
    int originBlock = movePlayer->getCurBlocks();
    int endBlocks = originBlock + forwardBlocks >= mapSize ? originBlock + forwardBlocks - mapSize : originBlock + forwardBlocks;
    movePlayer->setCurBlocks(endBlocks);
    endNode = (RichManMapNode*)mapNodes->objectAtIndex(endBlocks);
    if (curRound == 1) {
        CCNode* block = (CCNode*)mapNodes->objectAtIndex(0);
        aniArray->addObject(CCMoveTo::create(0, ccp(block->getPositionX() + posxDelta, block->getPositionY() + 20)));
        aniArray->addObject(CCFadeIn::create(0.5));
        aniArray->addObject(CCFadeOut::create(0.5));
        aniArray->addObject(CCFadeIn::create(0.5));
        aniArray->addObject(CCFadeOut::create(0.5));
        aniArray->addObject(CCFadeIn::create(0.5));
    }
    for (int i = 1; i <= forwardBlocks; i++) {
        CCNode* block = (CCNode*)mapNodes->objectAtIndex(originBlock + i >= mapSize ? originBlock + i - mapSize : originBlock + i);
        CCActionInterval* action = CCJumpTo::create(0.5f, ccp(block->getPositionX() + posxDelta, block->getPositionY() + 20), 10, 1);
        aniArray->addObject(action);
    }
    aniArray->addObject(CCCallFunc::create(this, callfunc_selector(RichManGameController::moveOver)));
    CCSequence* sequence = CCSequence::create(aniArray);
    movePlayer->move(sequence);
}

void RichManGameController::moveOver() {
    endNode->triggerEvent();
}

void RichManGameController::next() {
    if (curTurn == PLAYER2_TURN) {
        curRound ++;
    }
    curTurn = curTurn == PLAYER1_TURN ? PLAYER2_TURN : PLAYER1_TURN;
    getCurPlayer()->turnToForward();
}
