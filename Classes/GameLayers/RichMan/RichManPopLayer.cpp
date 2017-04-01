//
//  RichManPopLayer.cpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/4/1.
//
//

#include "RichManPopLayer.hpp"
#include "RichaManGameController.hpp"

bool RichManPopLayer::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    CCLayerColor* mask = CCLayerColor::create(ccc4(0, 0, 0, 155), winSize.width, winSize.height);
    this->addChild(mask);
    
    countDonwLabel =  NULL;
    fowardFlash = NULL;
    return true;
}

void RichManPopLayer::makeContentWithType(int type) {
    switch (type) {
        case GAME_START:
            countDonwLabel = CCLabelTTF::create("5", FONT_NAME, 40);
            countDonwLabel->setPosition(ccp(winSize.width / 2, winSize.height /2));
            this->addChild(countDonwLabel);
            this->schedule(schedule_selector(RichManPopLayer::countDown), 1);
            break;
        case GAME_FORWARD:
            fowardFlash = BoFlash::create("huishou");
            fowardFlash->setPosition(ccp(winSize.width / 2, winSize.height / 2));
            fowardFlash->playTo("stay1");
            this->addChild(fowardFlash);
            this->scheduleOnce(schedule_selector(RichManPopLayer::makeForwardBlocks), 0.5f);
            break;
    }
}

void RichManPopLayer::countDown() {
    int timeLeft = std::atoi(countDonwLabel->getString());
    timeLeft -= 1;
    if (timeLeft < 0) {
        this->unscheduleAllSelectors();
        this->removeFromParentAndCleanup(true);
        RichManGameController_->gameStart();
    } else if (timeLeft == 0) {
        countDonwLabel->setString("GO!");
    } else {
        countDonwLabel->setString(CCString::createWithFormat("%d", timeLeft)->getCString());
    }
}

void RichManPopLayer::makeForwardBlocks() {
    int blocks = arc4random() % 3 + 1;
    RichManGameController_->setForwardBlocks(blocks);
    fowardFlash->playTo(CCString::createWithFormat("play%i",blocks)->getCString());
    fowardFlash->returnFunc(CCCallFunc::create(this, callfunc_selector(RichManPopLayer::forwardOver)), false);
}

void RichManPopLayer::forwardOver() {
    this->scheduleOnce(schedule_selector(RichManPopLayer::closeLayer), 1.0f);
}

void RichManPopLayer::closeLayer() {
    this->removeFromParentAndCleanup(true);
    RichManGameController_->move();
}
