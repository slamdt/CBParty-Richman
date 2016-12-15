//
//  GameLayer.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-3-23.
//
//

#include "GameUtil.h"
#include "BattleLayer.h"

void GameUtil::RunScene(GameModel model) {
    CCDirector *director = CCDirector::sharedDirector();
    CCScene *scene = CCScene::create();
    CCLayer *pLayer = NULL;
    switch (model) {
        case GAME_BATTLE:
            pLayer = BattleLayer::create();
            break;
        default:
            pLayer = new BaseLayer();
            pLayer->autorelease();
            break;
    }
    if (pLayer) {
        scene->addChild(pLayer);
    }
    if (director->getRunningScene()) {
        director->replaceScene(scene);
    } else {
        director->runWithScene(scene);
    }
}