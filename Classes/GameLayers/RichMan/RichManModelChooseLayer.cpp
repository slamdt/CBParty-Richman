//
//  RichManModelChooseLayer.cpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/4/3.
//
//

#include "RichManModelChooseLayer.hpp"
#include "RichaManGameController.hpp"

bool RichManModelChooseLayer::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    
    CCLabelTTF* title = CCLabelTTF::create("I am rich man", FONT_NAME, 25);
    title->setColor(ccc3(255, 215, 0));
    title->setPosition(ccp(winSize.width / 2, winSize.height * 0.8));
    this->addChild(title);
    
    node = CCNode::create();
    this->addChild(node);
    
    CCMenuItemLabel* model1 = CCMenuItemLabel::create(CCLabelTTF::create("和好友对战", FONT_NAME, 18), this, menu_selector(RichManModelChooseLayer::chooseModel));
    model1->setTag(PLAY_WITH_PLAYER);
    model1->setColor(ccc3(255, 215, 0));
    model1->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.5));
    
    CCMenuItemLabel* model2 = CCMenuItemLabel::create(CCLabelTTF::create("和NPC对战", FONT_NAME, 18), this, menu_selector(RichManModelChooseLayer::chooseModel));
    model2->setTag(PLAY_WITH_NPC);
    model2->setColor(ccc3(218, 165, 105));
    model2->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.5));
    
    CCMenu* menu = CCMenu::create(model1, model2, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    node->addChild(menu);
    return true;
}

CCEditBox* RichManModelChooseLayer::createEditBox(int tag) {
    CCScale9Sprite *editboxBg = CCScale9Sprite::create("InputBg.png");
    CCEditBox* editbox = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), editboxBg);
    editbox->setTouchPriority(getTouchPriority());
    editbox->setFontName(FONT_NAME);
    editbox->setFontColor(ccc3(255,215,0));
    editbox->setFontSize(17);
    editbox->setInputMode(kEditBoxInputModeAny);
    editbox->setDelegate(this);
    editbox->setPlaceholderFontName(FONT_NAME);
    editbox->setPlaceHolder("输入游戏名称");
    editbox->setPlaceholderFontColor(ccc3(255, 215, 0));
    editbox->setTag(tag);
    return editbox;
}

void RichManModelChooseLayer::chooseModel(cocos2d::CCObject *pSender, cocos2d::CCTouch *pTouch) {
    int model = dynamic_cast<CCNode*>(pSender)->getTag();
    RichManGameController_->setGameModel(model);
    node->removeAllChildrenWithCleanup(true);
    if (model == PLAY_WITH_PLAYER) {
        CCLabelTTF* tips = CCLabelTTF::create("请输入自己游戏名称:", FONT_NAME, 14);
        tips->setColor(ccc3(0, 255, 0));
        tips->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.5));
        this->addChild(tips);
        
        CCEditBox* box = createEditBox(EDIT_SELF);
        box->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.4));
        this->addChild(box);
        
        tips = CCLabelTTF::create("请好友输入游戏名称:", FONT_NAME, 14);
        tips->setColor(ccc3(0, 255, 0));
        tips->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.5));
        this->addChild(tips);
        
        box = createEditBox(EDIT_FRIEND);
        box->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.4));
        this->addChild(box);
        
    } else if (model == PLAY_WITH_NPC) {
        CCLabelTTF* tips = CCLabelTTF::create("请输入自己游戏名称:", FONT_NAME, 14);
        tips->setColor(ccc3(0, 255, 0));
        tips->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
        this->addChild(tips);
        
        CCEditBox* box = createEditBox(EDIT_SELF);
        box->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.4));
        this->addChild(box);
    }
    
    CCMenuItemLabel* beginGameBtn = CCMenuItemLabel::create(CCLabelTTF::create("开始游戏", FONT_NAME, 20), this, menu_selector(RichManModelChooseLayer::beginGame));
    beginGameBtn->setColor(ccc3(0, 255, 0));
    beginGameBtn->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.25));
    
    CCMenu* menu = CCMenu::create(beginGameBtn, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    node->addChild(menu);
}

void RichManModelChooseLayer::beginGame() {
    if (!RichManGameController_->checkPlayerName()) {
        CCLayerColor* mask = CCLayerColor::create(ccc4(255, 0, 0, 255), winSize.width * 0.6, winSize.height * 0.1);
        mask->setPosition(ccp(winSize.width / 2 - mask->getContentSize().width / 2, winSize.height / 2));
        this->addChild(mask);
        
        CCLabelTTF* tipsLabel = CCLabelTTF::create("玩家名字不能为空，请重新填写", FONT_NAME, 15, CCSizeMake(mask->getContentSize().width * 0.9, 0), kCCTextAlignmentCenter);
        tipsLabel->setColor(ccc3(0, 0, 0));
        tipsLabel->setPosition(ccp(mask->getContentSize().width / 2, mask->getContentSize().height * 0.5));
        mask->addChild(tipsLabel);
        
        tipsLabel->runAction(CCSequence::create(CCDelayTime::create(2),
                                                CCFadeOut::create(0.5),
                                                CCFadeIn::create(0.5),
                                                CCFadeOut::create(0.5),
                                                CCFadeIn::create(0.5),
                                                CCFadeOut::create(0.5),
                                                CCFadeIn::create(0.5),
                                                CCCallFunc::create(mask, callfunc_selector(CCNode::removeFromParent)),
                                                NULL));
        return;
    }
    GameUtil::RunScene(RICH_MAN);
}

void RichManModelChooseLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
    
}

void RichManModelChooseLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text) {
    
}

void RichManModelChooseLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    
}

void RichManModelChooseLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    int editType = dynamic_cast<CCNode*>(editBox)->getTag();
    RichManGameController_->setPlayerName(editType, editBox->getText());
}
