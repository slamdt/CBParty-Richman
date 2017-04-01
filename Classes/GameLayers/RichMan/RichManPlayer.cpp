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
    score = 100;
    winSize = CCDirector::sharedDirector()->getWinSize();
    forwardBtn = NULL;
    curBlocks = -1;
    return true;
}

void RichManPlayer::initWithDatas(const char* modelName, bool isNeedFlip, bool isNPC) {
    hModel = HeroModel::Create(modelName, isNeedFlip);
    float posX = isNPC ? winSize.width - abs(hModel->GetWidth() / 2) : abs(hModel->GetWidth() / 2);
    hModel->setPosition(ccp(posX, winSize.height - hModel->GetHeight()));
    this->addChild(hModel);
    
    float anchorX = isNPC ? 1 : 0;
    float infoPosX = isNPC ? winSize.width - abs(hModel->GetWidth()) : abs(hModel->GetWidth());
    CCLabelTTF* nameLabel = CCLabelTTF::create(RichManGameController_->getPlayerName(isNPC), FONT_NAME, 13);
    nameLabel->setAnchorPoint(ccp(anchorX, 0.5));
    nameLabel->setPosition(ccp(infoPosX, hModel->getPositionY() + hModel->GetHeight() * 0.8));
    this->addChild(nameLabel);
    
    CCLabelTTF* scoreLabel = CCLabelTTF::create(CCString::createWithFormat("hp: %d", score)->getCString(), FONT_NAME, 13);
    scoreLabel->setAnchorPoint(ccp(anchorX, 0.5));
    scoreLabel->setPosition(ccp(infoPosX, hModel->getPositionY() + hModel->GetHeight() * 0.6));
    this->addChild(scoreLabel);
    
    if (!isNPC) {
        forwardBtn = CCMenuItemLabel::create(CCLabelTTF::create("点我前进", FONT_NAME, 15), this, menu_selector(RichManPlayer::forwardBtnDown));
        forwardBtn->setAnchorPoint(ccp(anchorX, 0.5));
        forwardBtn->setEnabled(false);
        forwardBtn->setPosition(ccp(infoPosX, hModel->getPositionY() + hModel->GetHeight() * 0.3));
        CCMenu* menu = CCMenu::create(forwardBtn, NULL);
        menu->setPosition(ccp(0, 0));
        this->addChild(menu);
    }
    
    movePic = CCSprite::create(CCString::createWithFormat("%s.png", modelName)->getCString());
    movePic->setScale(0.1);
    movePic->setVisible(false);
    this->addChild(movePic);
}

void RichManPlayer::turnToForward(bool isNPC) {
    if (!isNPC) {
        forwardBtn->setEnabled(true);
        forwardBtn->setColor(ccc3(0, 255, 0));
        forwardBtn->runAction(GameUtil::createHeartBeatAnimationAction());
    } else {
        
        makeForwardLayer();
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

void RichManPlayer::move(cocos2d::CCSequence *actSequence) {
    movePic->setVisible(true);
    movePic->runAction(actSequence);
}
