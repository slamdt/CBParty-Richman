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
    player = NULL;
    NPC = NULL;
    mapSize = 10;
    return true;
}

void RichManGameController::addMapNodes(RichManMapNode *node) {
    mapNodes->addObject(node);
}

void RichManGameController::setPlayer(RichManPlayer *_player, bool isNPC) {
    (isNPC ? NPC : player) = _player;
}

void RichManGameController::gameStart() {
    curRound = 1;
    curTurn = PLAYER_TURN;
    player->turnToForward(false);
}

const char* RichManGameController::getPlayerName(bool isNPC) {
    return isNPC ? "一只鸡" : "player";
}

void RichManGameController::setForwardBlocks(int block) {
    forwardBlocks = block;
}

void RichManGameController::move() {
    RichManPlayer* movePlayer = curTurn == PLAYER_TURN ? player : NPC;
    int posxDelta = curTurn == PLAYER_TURN ? -10 : 10;
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
    if (curTurn == NPC_TURN) {
        curRound ++;
    }
    curTurn = curTurn == PLAYER_TURN ? NPC_TURN : PLAYER_TURN;
    RichManPlayer* curPlayer = curTurn == PLAYER_TURN ? player : NPC;
    curPlayer->turnToForward(curTurn == NPC_TURN);
}
