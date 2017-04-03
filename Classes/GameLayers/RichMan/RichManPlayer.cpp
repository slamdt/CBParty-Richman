//
//  RichManPlayer.cpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/3/31.
//
//

#include "RichManPlayer.hpp"
#include "RichManPopLayer.hpp"
#include "RichaManGameController.hpp"

bool RichManPlayer::init() {
    if (!CCNode::init()) {
        return false;
    }
    score = 120;
    winSize = CCDirector::sharedDirector()->getWinSize();
    forwardBtn = NULL;
    commonTips = NULL;
    curBlocks = -1;
    scoreLabel = NULL;
    restRounds = 0;
    return true;
}

bool RichManPlayer::isPlayer2() {
    return playerId == PLAYER_2;
}

bool RichManPlayer::getIsNPC() {
    return isNPC;
}

int RichManPlayer::getPlayerId() {
    return playerId;
}

void RichManPlayer::initWithDatas(const char* modelName, bool isNeedFlip, bool _isNPC, int _playerId) {
    isNPC = _isNPC;
    playerId = _playerId;
    hModel = HeroModel::Create(modelName, isNeedFlip);
    float posX = isPlayer2() ? winSize.width - abs(hModel->GetWidth() / 2) : abs(hModel->GetWidth() / 2);
    hModel->setPosition(ccp(posX, winSize.height - hModel->GetHeight()));
    this->addChild(hModel);
    
    float anchorX = isPlayer2() ? 1 : 0;
    float infoPosX = isPlayer2() ? winSize.width - abs(hModel->GetWidth()) : abs(hModel->GetWidth());
    CCLabelTTF* nameLabel = CCLabelTTF::create(RichManGameController_->getPlayerName(playerId), FONT_NAME, 13);
    nameLabel->setAnchorPoint(ccp(anchorX, 0.5));
    nameLabel->setPosition(ccp(infoPosX, hModel->getPositionY() + hModel->GetHeight() * 0.8));
    this->addChild(nameLabel);
    
    scoreLabel = CCLabelTTF::create(CCString::createWithFormat("学力: %d", score)->getCString(), FONT_NAME, 13);
    scoreLabel->setAnchorPoint(ccp(anchorX, 0.5));
    scoreLabel->setPosition(ccp(infoPosX, hModel->getPositionY() + hModel->GetHeight() * 0.6));
    this->addChild(scoreLabel);
    
    if (!isNPC) {
        forwardBtn = CCMenuItemLabel::create(CCLabelTTF::create("点我前进", FONT_NAME, 15), this, menu_selector(RichManPlayer::forwardBtnDown));
        forwardBtn->setAnchorPoint(ccp(anchorX, 0.5));
        forwardBtn->setEnabled(false);
        forwardBtn->setPosition(ccp(infoPosX, hModel->getPositionY() + hModel->GetHeight() * 0.3));
        CCMenu* menu = CCMenu::create(forwardBtn, NULL);
        menu->setTouchPriority(0);
        menu->setPosition(ccp(0, 0));
        this->addChild(menu);
    }
    
    movePic = CCSprite::create(CCString::createWithFormat("%s.png", modelName)->getCString());
    movePic->setScale(0.1);
    movePic->setVisible(false);
    this->addChild(movePic);
    
    RichManGameController_->setPlayer(this, playerId);
}

void RichManPlayer::restOver() {
    RichManGameController_->next();
}

void RichManPlayer::turnToForward() {
    if (restRounds > 0) {
        restRounds --;
        if (commonTips) {
            commonTips->removeFromParentAndCleanup(true);
            commonTips = NULL;
        }
        commonTips = CCLabelTTF::create(CCString::createWithFormat("%s装逼休息中...", RichManGameController_->getPlayerName(playerId))->getCString(), FONT_NAME, 20);
        commonTips->setPosition(ccp(winSize.width / 2, winSize.height * 0.7));
        commonTips->setColor(ccc3(0, 255, 0));
        commonTips->runAction(CCSequence::create(CCDelayTime::create(1),
                                                 CCFadeOut::create(2),
                                                 CCCallFunc::create(this, callfunc_selector(RichManPlayer::restOver)),
                                                 NULL));
        this->getParent()->addChild(commonTips);
        return;
    }
    if (!isNPC) {
        forwardBtn->setEnabled(true);
        forwardBtn->setColor(ccc3(0, 255, 0));
        forwardBtn->runAction(GameUtil::createHeartBeatAnimationAction());
    } else {
        if (commonTips) {
            commonTips->removeFromParentAndCleanup(true);
            commonTips = NULL;
        }
        commonTips = CCLabelTTF::create("现在轮到一只鸡咯~耐心等待一下吧", FONT_NAME, 18);
        commonTips->setPosition(ccp(winSize.width / 2, winSize.height * 0.7));
        commonTips->setColor(ccc3(0, 255, 0));
        commonTips->runAction(CCSequence::create(CCDelayTime::create(1),
                                           CCFadeOut::create(1),
                                           CCCallFunc::create(this, callfunc_selector(RichManPlayer::makeForwardLayer)),
                                           NULL));
        this->getParent()->addChild(commonTips);
    }
}

void RichManPlayer::forwardBtnDown(cocos2d::CCObject *pSender, cocos2d::CCTouch *pTouch) {
    forwardBtn->setEnabled(false);
    forwardBtn->stopAllActions();
    makeForwardLayer();
}

void RichManPlayer::makeForwardLayer() {
    RichManPopLayer* forwardLayer = RichManPopLayer::create();
    forwardLayer->makeContentWithType(GAME_FORWARD);
    this->getParent()->addChild(forwardLayer);
}

int RichManPlayer::getCurBlocks() {
    return curBlocks;
}

void RichManPlayer::setCurBlocks(int blocks) {
    curBlocks = blocks;
}

int RichManPlayer::getScore() {
    return score;
}

void RichManPlayer::setScore(int scoreDelta) {
    score += scoreDelta;
    score = score < 0 ? 0 : score;
    scoreLabel->setString(CCString::createWithFormat("学力: %d", score)->getCString());
    if (score == 0) {
        RichManPopLayer* layer = RichManPopLayer::create();
        layer->showGameOver(playerId);
        this->getParent()->addChild(layer);
    }
}

void RichManPlayer::setRestRound(int _restRounds) {
    restRounds = _restRounds;
}

void RichManPlayer::move(cocos2d::CCSequence *actSequence) {
    movePic->setVisible(true);
    movePic->runAction(actSequence);
}
