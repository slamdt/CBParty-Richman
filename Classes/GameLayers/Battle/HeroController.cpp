//
//  HeroController.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#include "HeroController.h"

HeroController* HeroController::create(const char* heroName,bool isNeedFlip) {
    HeroController* p = new HeroController(heroName,isNeedFlip);
    p->makeHero();
    p->autorelease();
    return p;
}

void HeroController::makeHero() {
    pHero = HeroModel::Create(_heroName,_isNeedFlip);
    heroHeight = pHero->GetHeight();
    this->addChild(pHero);
}

void HeroController::fight(FightMode mode,CCObject* target,cocos2d::SEL_CallFunc selector) {
    const char* fightWords = "";
    if (mode == FIGHT_ATTACT) {
        fightWords = "操你妹！";
    } else if (mode == FIGHT_DEFENSE) {
        fightWords = "你特么再说一遍？";
    } else if (mode == FIGHT_CHAOFENG) {
        fightWords = "小鸡鸡，快点我，让我干他!";
    }
    if (pHero) {
        pTarget = target;
        pSelector = selector;
        pHero->PlayAnimation("gongji");
        if (fightEffect) {
            fightEffect->removeFromParentAndCleanup(true);
        }
        fightEffect = CCLabelTTF::create(fightWords, FONT_NAME, 20);
        fightEffect->setPosition(ccp(0, heroHeight * 1.3));
        this->addChild(fightEffect);
        fightEffect->runAction(CCSequence::createWithTwoActions(CCFadeOut::create(2), CCCallFunc::create(this, callfunc_selector(HeroController::fightOver))));
    }
}

void HeroController::fightOver() {
    fightEffect->removeFromParentAndCleanup(true);
    fightEffect = NULL;
    if (pTarget && pSelector) {
        (pTarget->*pSelector)();
    }
}