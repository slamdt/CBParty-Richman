//
//  BattleScene.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#include "BattleLayer.h"
#include "HeroModel.h"

BattleLayer::~BattleLayer() {
    players->removeAllObjects();
    players->release();
    players = NULL;
}

bool BattleLayer::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    players = CCArray::create();
    players->retain();
    
    HeroController *playerSelf = HeroController::create("ailisi_1",true);
    playerSelf->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.5));
    this->addChild(playerSelf);
    players->addObject(playerSelf);
    
    HeroController *playerEnermy = HeroController::create("ailun_1");
    this->addChild(playerEnermy);
    playerEnermy->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.5));
    players->addObject(playerEnermy);
    
    selfFight = CCMenuItemLabel::create(CCLabelTTF::create("攻击", FONT_NAME, 20), this,menu_selector(BattleLayer::Fight));
    selfFight->setTag(PLAYER_SELF);
    selfFight->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.3));
    
    enermyFight = CCMenuItemLabel::create(CCLabelTTF::create("攻击", FONT_NAME, 20), this,menu_selector(BattleLayer::Fight));
    enermyFight->setTag(PLAYER_ENERMY);
    enermyFight->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.3));
    CCMenu *menu = CCMenu::create(selfFight,enermyFight,NULL);
    menu->setPosition(0, 0);
    this->addChild(menu);
    
    return true;
}

void BattleLayer::setButtonEnable(bool status) {
    selfFight->setEnabled(status);
    enermyFight->setEnabled(status);
}

void BattleLayer::Fight(cocos2d::CCObject *pSender, cocos2d::CCTouch *pTouch) {
    setButtonEnable(false);
    playerTurn = dynamic_cast<CCNode*>(pSender)->getTag();
    ((HeroController*)players->objectAtIndex(playerTurn))->fight(FIGHT_ATTACT,this,callfunc_selector(BattleLayer::FightOver));;
}

void BattleLayer::FightOver() {
    playerTurn = playerTurn == PLAYER_SELF ? PLAYER_ENERMY : PLAYER_SELF;
    ((HeroController*)players->objectAtIndex(playerTurn))->fight(FIGHT_DEFENSE,this,callfunc_selector(BattleLayer::defenseOver));
}

void BattleLayer::defenseOver() {
    setButtonEnable(true);
    ((HeroController*)players->objectAtIndex(playerTurn))->fight(FIGHT_CHAOFENG,NULL,NULL);
}