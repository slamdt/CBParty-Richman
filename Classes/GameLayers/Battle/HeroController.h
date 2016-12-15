//
//  HeroController.h
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#ifndef __DoTaBattle__HeroController__
#define __DoTaBattle__HeroController__

#include "HeroModel.h"

class HeroController : public cocos2d::CCNode {
public:
    HeroController(const char* heroName,bool isNeedFlip) : _heroName(heroName),_isNeedFlip(isNeedFlip),fightEffect(NULL),pTarget(NULL),pSelector(NULL) {
        
    }
    static HeroController* create(const char* heroName,bool isNeedFlip = false);
    void makeHero();
    void fight(FightMode mode, CCObject* target,cocos2d::SEL_CallFunc selector);
    void fightOver();
private:
    const char* _heroName;
    bool _isNeedFlip;
    HeroModel *pHero;
    float heroHeight;
    CCLabelTTF *fightEffect;
    CCObject *pTarget;
    SEL_CallFunc pSelector;
};

#endif /* defined(__DoTaBattle__HeroController__) */
