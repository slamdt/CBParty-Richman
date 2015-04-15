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

using namespace cocos2d;

#define WINSIZE GameLayer::instance()->getWinSize()
#define GameLayer_ GameLayer::instance()
#define FONT_NAME "FZYHJW--GB1-0" 

class GameLayer : public CCLayer {
public:
    static CCScene* scene();
    static GameLayer* instance();
    bool init();
    CCSize getWinSize() { return winSize; };
private:
    CCSize winSize;
    static GameLayer* _layer;
};

#endif /* defined(__DoTaBattle__GameLayer__) */
