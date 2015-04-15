//
//  GameLayer.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-3-23.
//
//

#include "GameLayer.h"
#include "CCArmatureDataManager.h"
#include "CCArmature.h"

GameLayer* GameLayer::_layer = NULL;

GameLayer* GameLayer::instance() {
    if (_layer == NULL) {
        _layer = new GameLayer();
        CCAssert(_layer->init(), "gameLayer init fialed");
    }
    return _layer;
}

CCScene* GameLayer::scene() {
    CCScene *pScene = CCScene::create();
    GameLayer *pLayer = GameLayer::instance();
    pScene->addChild(pLayer);
    return pScene;
}

bool GameLayer::init() {
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *tip = CCLabelTTF::create("hello world", FONT_NAME, 20);
    tip->setPosition(ccp(winSize.width/2, winSize.height*0.9));
    this->addChild(tip);
    
    cocos2d::extension::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bao_lv02.pvr.ccz","bao_lv02.plist","bao_lv02.xml");
    cocos2d::extension::CCArmature* m_pAnimator = cocos2d::extension::CCArmature::create("bao_lv02");
    m_pAnimator->setPosition(winSize/2);
    this->addChild(m_pAnimator);
    
    return true;
}