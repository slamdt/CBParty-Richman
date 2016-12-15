//
//  BattleScene.h
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#ifndef __DoTaBattle__BattleScene__
#define __DoTaBattle__BattleScene__

#include "BaseLayer.h"
#include "HeroController.h"

class BattleLayer : public BaseLayer{
public:
    CREATE_FUNC(BattleLayer)
    virtual bool init();
    void Fight(CCObject *pSender, CCTouch *pTouch);
    void FightOver();
    void defenseOver();
    void setButtonEnable(bool status);
private:
    enum {
        PLAYER_SELF = 0,
        PLAYER_ENERMY,
    };
    CCMenuItemLabel *selfFight;
    CCMenuItemLabel *enermyFight;
    CCArray *players;
    int playerTurn;
    ~BattleLayer();
};

#endif /* defined(__DoTaBattle__BattleScene__) */
