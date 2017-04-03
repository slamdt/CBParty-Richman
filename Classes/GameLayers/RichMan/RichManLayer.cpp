//
//  RichManLayer.cpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/3/18.
//
//

#include "RichManLayer.hpp"
#include "RichaManGameController.hpp"
#include "RichManMapNode.hpp"
#include "RichManPlayer.hpp"
#include "RichManPopLayer.hpp"

bool RichManLayer::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    CCLabelTTF *tips = CCLabelTTF::create("I'm RichMan", FONT_NAME, 20);
    tips->setColor(ccc3(255, 215, 0));
    tips->setPosition(ccp(winSize.width / 2 , winSize.height * 0.6));
    this->addChild(tips);
    
    drawMap();
    
    RichManPlayer* player = RichManPlayer::create();
    player->initWithDatas("ailisi_1", true, false, PLAYER_1);
    this->addChild(player);
    
    RichManPlayer* NPC = RichManPlayer::create();
    NPC->initWithDatas("ailun_1", false, RichManGameController_->getIsPlayWithNPC(), PLAYER_2);
    this->addChild(NPC);
    
    CCMenuItemLabel* backBtn = CCMenuItemLabel::create(CCLabelTTF::create("返回模式选择界面", FONT_NAME, 20), this, menu_selector(RichManLayer::backToModel));
    backBtn->setColor(ccc3(255, 97, 0));
    backBtn->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    
    CCMenu* menu = CCMenu::create(backBtn, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    RichManPopLayer* startLayer = RichManPopLayer::create();
    startLayer->makeContentWithType(GAME_START);
    this->addChild(startLayer);
    return true;
}

void RichManLayer::drawMap() {
    float posX = 0.0f;
    float posY = 0.0f;
    for (int i = 0; i < 10; i++) {
        RichManMapNode* node = RichManMapNode::create();
        int nodeType = 1;
        if (i == 1 || i == 3 || i == 6 || i == 8 ) {
            nodeType = 0;
        } else if (i == 5) {
            nodeType = 2;
        }
        node->initWithDatas(i, nodeType);
        if (i < 6) {
            posX = winSize.width * 0.1 + i * winSize.width / 6;
            if (i < 3) {
                posY = winSize.height / 2 + i * winSize.height / 6;
            } else {
                posY = winSize.height / 2 + (5 - i) * winSize.height / 6;
            }
        } else {
            posX -= winSize.width / 6;
            if (i < 8) {
                posY -= winSize.height / 6;
            } else if (i == 9) {
                posY += winSize.height / 6;
            }
        }
        node->setPosition(ccp(posX, posY));
        this->addChild(node);
        RichManGameController_->addMapNodes(node);
    }
}

void RichManLayer::backToModel() {
    RichManGameController_->resetData();
    GameUtil::RunScene(RICH_MAN_MODEL_CHOOSE);
}
