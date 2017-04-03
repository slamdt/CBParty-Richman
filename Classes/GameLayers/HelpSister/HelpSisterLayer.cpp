//
//  HelpSisterLayer.cpp
//  DoTaBattle
//
//  Created by yuyu on 17/1/11.
//
//

#include "HelpSisterLayer.hpp"

bool HelpSisterLayer::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *tips = CCLabelTTF::create("献给谭帅的大表妹", FONT_NAME, 20);
    tips->setPosition(ccp(winSize.width / 2, winSize.height * 0.8));
    tips->runAction(CCMoveTo::create(2, ccp(winSize.width, winSize.height * 0.8)));
    tips->runAction(CCFadeOut::create(2));
    
    this->addChild(tips);
    layerNode = CCNode::create();
    this->addChild(layerNode);
//    makeLayerByType(LOGIN_LAYER);
    return true;
}

void HelpSisterLayer::makeLayerByType(LayerType type) {
    switch (type) {
        case LOGIN_LAYER:
            showLogin();
            break;
        case REGISIST_LAYER:
            break;
        case PLAY_LAYER:
            break;
    }
}

void HelpSisterLayer::showLogin() {
    layerNode->removeAllChildrenWithCleanup(true);
    
    CCLabelTTF *accountTip = CCLabelTTF::create("用户名", FONT_NAME, 20);
    accountTip->setPosition(ccp(winSize.width * 0.3,winSize.height * 0.6));
    layerNode->addChild(accountTip);
    
    CCScale9Sprite *accountEditbixBg = CCScale9Sprite::create("InputBg.png");
    CCEditBox* accountEditbix = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), accountEditbixBg);
    accountEditbix->setTouchPriority(getTouchPriority());
    accountEditbix->setFontName(FONT_NAME);
    accountEditbix->setFontColor(ccc3(0,0,0));
    accountEditbix->setFontSize(15);
    accountEditbix->setInputMode(kEditBoxInputModeAny);
    accountEditbix->setDelegate(this);
    accountEditbix->setPosition(ccp(winSize.width * 0.55, accountTip->getPositionY()));
    accountEditbix->setPlaceholderFontName(FONT_NAME);
    accountEditbix->setPlaceHolder("input your account");
    accountEditbix->setPlaceholderFontColor(ccc3(0, 0, 0));
    accountEditbix->setTag(ACCOUNT);
    layerNode->addChild(accountEditbix);
    
    CCLabelTTF *passTip = CCLabelTTF::create("密码", FONT_NAME, 20);
    passTip->setPosition(ccp(winSize.width * 0.3,winSize.height * 0.5));
    layerNode->addChild(passTip);
    
    CCScale9Sprite *passEditbixBg = CCScale9Sprite::create("InputBg.png");
    CCEditBox* passEditbix = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), passEditbixBg);
    passEditbix->setTouchPriority(getTouchPriority());
    passEditbix->setFontName(FONT_NAME);
    passEditbix->setFontColor(ccc3(0,0,0));
    passEditbix->setFontSize(15);
    passEditbix->setInputMode(kEditBoxInputModeAny);
    passEditbix->setDelegate(this);
    passEditbix->setPosition(ccp(winSize.width * 0.55, passTip->getPositionY()));
    passEditbix->setPlaceholderFontName(FONT_NAME);
    passEditbix->setPlaceHolder("input your password");
    passEditbix->setPlaceholderFontColor(ccc3(0, 0, 0));
    passEditbix->setTag(PASSWORD);
    layerNode->addChild(passEditbix);

    CCMenuItemLabel *loginBtn = CCMenuItemLabel::create(CCLabelTTF::create("登陆", FONT_NAME, 20), this, menu_selector(HelpSisterLayer::startLogin));
    loginBtn->setPosition(ccp(winSize.width * 0.4, winSize.height * 0.3));
    
    CCMenuItemLabel *regisitBtn = CCMenuItemLabel::create(CCLabelTTF::create("注册", FONT_NAME, 20), this, menu_selector(HelpSisterLayer::startRegisit));
    regisitBtn->setPosition(ccp(winSize.width * 0.6, winSize.height * 0.3));
    
    CCMenu *menu = CCMenu::create(loginBtn,regisitBtn,NULL);
    menu->setTouchPriority(getTouchPriority());
    menu->setPosition(ccp(0, 0));
    layerNode->addChild(menu);
}

void HelpSisterLayer::startLogin(cocos2d::CCObject *pSender, cocos2d::CCTouch *ptouch) {
    if (!checkLogin()) {
        CCMessageBox("用户密码不对或用户不存在", "登录失败");
    }
}

bool HelpSisterLayer::checkLogin() {
    for(std::vector<player>::iterator it = players.begin(); it != players.end(); it++) {
        if (std::strcmp(it->account.c_str(), accountStr.c_str()) == 0 && std::strcmp(it->password.c_str(), passwordStr.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

void HelpSisterLayer::startRegisit(cocos2d::CCObject *pSender, cocos2d::CCTouch *ptouch) {
    
}

void HelpSisterLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
    
}

void HelpSisterLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    
}

void HelpSisterLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    int type = dynamic_cast<CCNode*>(editBox)->getTag();
    if (type == ACCOUNT) {
        accountStr = editBox->getText();
    } else if (type == PASSWORD) {
        passwordStr = editBox->getText();
    }
    
}

void HelpSisterLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text) {
    
}
