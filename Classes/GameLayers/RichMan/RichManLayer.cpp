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
    tips->setPosition(ccp(winSize.width / 2 , winSize.height * 0.5));
    this->addChild(tips);
    
    drawMap();
    
    RichManPlayer* player = RichManPlayer::create();
    player->initWithDatas("ailisi_1", true);
    this->addChild(player);
    RichManGameController_->setPlayer(player, false);
    
    RichManPlayer* NPC = RichManPlayer::create();
    NPC->initWithDatas("ailun_1", false, true);
    this->addChild(NPC);
    RichManGameController_->setPlayer(NPC, true);
    
    RichManPopLayer* startLaye = RichManPopLayer::create();
    startLaye->makeContentWithType(GAME_START);
    this->addChild(startLaye);
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
