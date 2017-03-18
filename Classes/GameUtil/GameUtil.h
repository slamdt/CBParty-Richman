//
//  GameLayer.h
//  DoTaBattle
//
//  Created by yuyu on 15-3-23.
//
//

#ifndef __DoTaBattle__GameLayer__
#define __DoTaBattle__GameLayer__

#include "cocos2d.h"
#include "CCEditBox.h"
using namespace cocos2d;
using namespace cocos2d::extension;

#define FONT_NAME "FZYHJW--GB1-0" 
enum GameModel{
    GAME_BATTLE = 0,
    HELP_SISTER
};

enum FightMode {
    FIGHT_ATTACT = 0,
    FIGHT_DEFENSE,
    FIGHT_CHAOFENG
};
class GameUtil {
public:
    static void RunScene(GameModel model);
private:
};

#endif /* defined(__DoTaBattle__GameLayer__) */
