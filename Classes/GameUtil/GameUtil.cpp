//
//  GameLayer.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-3-23.
//
//

#include "GameUtil.h"
#include "BattleLayer.h"
#include "HelpSisterLayer.hpp"
#include "RichManLayer.hpp"

void GameUtil::RunScene(GameModel model) {
    CCDirector *director = CCDirector::sharedDirector();
    CCScene *scene = CCScene::create();
    CCLayer *pLayer = NULL;
    switch (model) {
        case GAME_BATTLE:
            pLayer = BattleLayer::create();
            break;
        case HELP_SISTER:
            pLayer = HelpSisterLayer::create();
            break;
        case RICH_MAN:
            pLayer = RichManLayer::create();
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

CCAction* GameUtil::createHeartBeatAnimationAction() {
    CCFiniteTimeAction *sequence = CCSequence::create(CCScaleTo::create(0.1f, 1.3f),
                                                      CCScaleTo::create(0.2f, 1.0f),
                                                      CCScaleTo::create(0.1f, 1.3f),
                                                      CCScaleTo::create(0.2f, 1.0f),
                                                      CCDelayTime::create(1.5f),
                                                      NULL);
    return CCRepeatForever::create(dynamic_cast<CCActionInterval*>(sequence));
}
