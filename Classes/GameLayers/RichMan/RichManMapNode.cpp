//
//  RichManMapNode.cpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/3/31.
//
//

#include "RichManMapNode.hpp"
#include "RichaManGameController.hpp"

bool RichManMapNode::init() {
    if (!CCNode::init()) {
        return false;
    }
    return true;
}

void RichManMapNode::initWithDatas(int step, int nodeType) {
    curStep = step + 1;
    const char* nodePicFile = "";
    switch (nodeType) {
        case BLOCK_EMPTY:
            nodePicFile = "block_empty.png";
            break;
        case BLOCK_SHOP:
            nodePicFile = "block_shop.png";
            break;
        case BLOCK_RANDOM:
            nodePicFile = "block_random.png";
            break;
    }
    CCSprite* nodePic = CCSprite::create(nodePicFile);
    this->addChild(nodePic);
    
    CCLabelTTF* stepLabel = CCLabelTTF::create(CCString::createWithFormat("%d", curStep)->getCString(), FONT_NAME, 15);
    stepLabel->setAnchorPoint(ccp(0.5, 0));
    stepLabel->setColor(ccc3(255, 0, 0));
    stepLabel->setPosition(ccp(nodePic->getContentSize().width / 2, nodePic->getContentSize().height * 0.4));
    nodePic->addChild(stepLabel);
}

void RichManMapNode::triggerEvent() {
    RichManGameController_->next();
}
