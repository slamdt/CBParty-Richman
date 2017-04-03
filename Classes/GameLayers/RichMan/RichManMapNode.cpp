//
//  RichManMapNode.cpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/3/31.
//
//

#include "RichManMapNode.hpp"
#include "RichaManGameController.hpp"
#include "RichManPopLayer.hpp"

bool RichManMapNode::init() {
    if (!CCNode::init()) {
        return false;
    }
    return true;
}

void RichManMapNode::initWithDatas(int step, int type) {
    nodeType = type;
    curStep = step + 1;
    const char* nodePicFile = "";
    switch (nodeType) {
        case BLOCK_EMPTY:
        {
            nodePicFile = "block_empty.png";
        }
            break;
        case BLOCK_SHOP:
        {
            nodePicFile = "block_shop.png";
        }
            break;
        case BLOCK_RANDOM:
        {
            nodePicFile = "block_random.png";
        }
            break;
    }
    nodePic = CCSprite::create(nodePicFile);
    this->addChild(nodePic);
    
    CCLabelTTF* stepLabel = CCLabelTTF::create(CCString::createWithFormat("%d", curStep)->getCString(), FONT_NAME, 15);
    stepLabel->setPositionY(nodePic->getContentSize().height * 0.15);
    stepLabel->setColor(ccc3(255, 0, 0));
    this->addChild(stepLabel);
}

void RichManMapNode::setHolderInfo(int playerId, Json::Value question) {
    holderInfo["questions"].append(question);
    if (holderInfo["questions"].size() > 1) {
        return;
    }
    holderInfo["playerId"] = playerId;
    nodeType = BLOCK_HOLDED;
    if (nodePic) {
        nodePic->removeFromParentAndCleanup(true);
    }
    nodePic = CCSprite::create("block_holded.png");
    this->addChild(nodePic);
    CCLabelTTF* holderName = CCLabelTTF::create(RichManGameController_->getPlayerName(playerId), FONT_NAME, 15);
    holderName->setColor(ccc3(255, 215, 0));
    holderName->setPosition(ccp(nodePic->getContentSize().width / 2, 0));
    nodePic->addChild(holderName);
}

void RichManMapNode::reduceHolderQuestions(int reduceSize) {
    holderInfo["questions"].resize(holderInfo["questions"].size() - reduceSize);
}

Json::Value& RichManMapNode::getHolderInfo() {
    return holderInfo;
}

void RichManMapNode::clearHolderInfo() {
    holderInfo.clear();
}

void RichManMapNode::freeHoldedBlock() {
    clearHolderInfo();
    nodeType = BLOCK_EMPTY;
    if (nodePic) {
        nodePic->removeFromParentAndCleanup(true);
    }
    nodePic = CCSprite::create("block_empty.png");
    this->addChild(nodePic);
}

void RichManMapNode::triggerEvent() {
    RichManPopLayer* popLayer = RichManPopLayer::create();
    int popType;
    switch (nodeType) {
        case BLOCK_EMPTY:
        {
            popType = GAME_BUILD;
        }
            break;
        case BLOCK_SHOP:
        {
            popType = GAME_SHOP;
        }
            break;
        case BLOCK_RANDOM:
        {
            popType = GAME_RANDOM;
        }
            break;
        case BLOCK_HOLDED:
        {
            popType = GAME_CROSS;
        }
            break;
    }
    popLayer->makeContentWithType(popType);
    this->getParent()->addChild(popLayer);
}
