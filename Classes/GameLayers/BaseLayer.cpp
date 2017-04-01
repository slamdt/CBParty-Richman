//
//  BaseLayer.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#include "BaseLayer.h"

bool BaseLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    return true;
}
