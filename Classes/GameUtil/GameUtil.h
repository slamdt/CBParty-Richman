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
#include "BoFlash.h"
using namespace cocos2d;
using namespace cocos2d::extension;

#define SINGLETON(className)\
private:\
className(){};\
virtual bool init();\
static className* _shared;\
public:\
static className* shared(){\
if(!_shared) {_shared = new className();_shared->init();}\
return _shared;\
};\
void destroy() {if(_shared) {delete _shared; _shared = NULL;}};\

#define SINGLETON_IMPL(className)\
className* className::_shared = NULL;\


#define FONT_NAME "FZYHJW--GB1-0" 
enum GameModel{
    GAME_BATTLE = 0,
    HELP_SISTER,
    RICH_MAN
};

enum FightMode {
    FIGHT_ATTACT = 0,
    FIGHT_DEFENSE,
    FIGHT_CHAOFENG
};

enum RICHMANPOPTYPE {
    GAME_START = 0,
    GAME_FORWARD
};
class GameUtil {
public:
    static void RunScene(GameModel model);
    static CCAction* createHeartBeatAnimationAction();
private:
};

#endif /* defined(__DoTaBattle__GameLayer__) */
