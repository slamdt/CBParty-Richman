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
    countDonwLabel =  NULL;
    fowardFlash = NULL;
    setNode = NULL;
    bg = NULL;
    setTouchEnabled(true);
    setIsSwallowTouch(true);
    return true;
}

void RichManPopLayer::makeContentWithType(int type) {
    layerType = type;
    switch (layerType) {
        case GAME_START:
        {
            CCLayerColor* mask = CCLayerColor::create(ccc4(0, 0, 0, 155), winSize.width, winSize.height);
            this->addChild(mask);
            countDonwLabel = CCLabelTTF::create("5", FONT_NAME, 40);
            countDonwLabel->setPosition(ccp(winSize.width / 2, winSize.height /2));
            this->addChild(countDonwLabel);
            this->schedule(schedule_selector(RichManPopLayer::countDown), 1);
        }
            break;
        case GAME_FORWARD:
        {
            CCLayerColor* mask = CCLayerColor::create(ccc4(0, 0, 0, 155), winSize.width, winSize.height);
            this->addChild(mask);
            fowardFlash = BoFlash::create("huishou");
            fowardFlash->setPosition(ccp(winSize.width / 2, winSize.height / 2));
            fowardFlash->playTo("stay1");
            this->addChild(fowardFlash);
            this->scheduleOnce(schedule_selector(RichManPopLayer::makeForwardBlocks), 0.5f);
        }
            break;
        case GAME_BUILD:
        {
            makeGameBuildPop();
        }
            break;
        case GAME_CROSS:
        {
            makeGameCrossPop();
        }
            break;
        case GAME_RANDOM:
        {
            CCLayerColor* mask = CCLayerColor::create(ccc4(128, 138, 135, 255), winSize.width * 0.7, winSize.height * 0.2);
            mask->setPosition(ccp(winSize.width / 2 - mask->getContentSize().width / 2, winSize.height / 2));
            this->addChild(mask);
            
            const char* tips = "";
            ccColor3B color = ccc3(0, 0, 0);
            int randomType = arc4random() % 3;
            if (randomType == RANDOM_INCREASE_SCORE) {
                tips = "哇哦，%s在学校诗词歌赋大赛获得了一等奖，奖励30学力！";
                color = ccc3(255, 215, 0);
                RichManGameController_->setCurPlayerScore(30);
            } else if (randomType == RANDOM_DECREASE_SCORE) {
                tips = "好惨啊，%s在去上学的路上被抢劫了，损失30学力，555";
                color = ccc3(255, 0, 0);
                RichManGameController_->setCurPlayerScore(-30);
            } else if (randomType == RANDOM_STOP_FOR_2_ROUND) {
                color = ccc3(0, 255, 0);
                tips = "%s说：人生不仅是眼前和苟且，还有诗和远方，休息2回合，装个B";
                RichManGameController_->setRestRound(2);
            }
            
            CCLabelTTF* tipsLabel = CCLabelTTF::create(CCString::createWithFormat(tips, RichManGameController_->getCurPlayerName())->getCString(), FONT_NAME, 15, CCSizeMake(mask->getContentSize().width * 0.9, 0), kCCTextAlignmentCenter);
            tipsLabel->setColor(color);
            tipsLabel->setPosition(ccp(mask->getContentSize().width / 2, mask->getContentSize().height * 0.5));
            mask->addChild(tipsLabel);
            
            tipsLabel->runAction(CCSequence::create(CCDelayTime::create(3),
                                                    CCFadeOut::create(0.5),
                                                    CCFadeIn::create(0.5),
                                                    CCFadeOut::create(0.5),
                                                    CCFadeIn::create(0.5),
                                                    CCFadeOut::create(0.5),
                                                    CCFadeIn::create(0.5),
                                                    CCCallFunc::create(this, callfunc_selector(RichManPopLayer::closeLayer)),
                                                    NULL));
        }
            break;
        case GAME_SHOP:
        {
            CCLayerColor* mask = CCLayerColor::create(ccc4(245, 222, 179, 255), winSize.width * 0.7, winSize.height * 0.2);
            mask->setPosition(ccp(winSize.width / 2 - mask->getContentSize().width / 2, winSize.height / 2));
            this->addChild(mask);
            
            CCLabelTTF* tipsLabel = CCLabelTTF::create("商城正在建造当中，尽请期待。。。", FONT_NAME, 15, CCSizeMake(mask->getContentSize().width * 0.9, 0), kCCTextAlignmentCenter);
            tipsLabel->setColor(ccc3(127, 235, 0));
            tipsLabel->setPosition(ccp(mask->getContentSize().width / 2, mask->getContentSize().height * 0.5));
            mask->addChild(tipsLabel);
            
            tipsLabel->runAction(CCSequence::create(CCDelayTime::create(2),
                                                    CCFadeOut::create(0.5),
                                                    CCFadeIn::create(0.5),
                                                    CCFadeOut::create(0.5),
                                                    CCFadeIn::create(0.5),
                                                    CCFadeOut::create(0.5),
                                                    CCFadeIn::create(0.5),
                                                    CCCallFunc::create(this, callfunc_selector(RichManPopLayer::closeLayer)),
                                                    NULL));
        }
            break;
    }
}

void RichManPopLayer::showGameOver(int loserId) {
    CCLayerColor* mask = CCLayerColor::create(ccc4(128, 138, 135, 255), winSize.width * 0.8, winSize.height * 0.7);
    mask->setPosition(ccp(winSize.width / 2 - mask->getContentSize().width / 2, winSize.height / 2));
    this->addChild(mask);
    
    CCLabelTTF* tipsLabel = CCLabelTTF::create(CCString::createWithFormat("%s的学历已耗尽，游戏结束，%s获得了胜利，鼓掌。。。", RichManGameController_->getPlayerName(loserId), RichManGameController_->getTheOtherPlayerName(loserId))->getCString(), FONT_NAME, 15, CCSizeMake(mask->getContentSize().width * 0.9, 0), kCCTextAlignmentCenter);
    tipsLabel->setColor(ccc3(255, 215, 0));
    tipsLabel->setPosition(ccp(mask->getContentSize().width / 2, mask->getContentSize().height * 0.5));
    mask->addChild(tipsLabel);
    
    CCMenuItemLabel* returnBtn = CCMenuItemLabel::create(CCLabelTTF::create("返回主界面", FONT_NAME, 20), this, menu_selector(RichManPopLayer::backToModel));
    returnBtn->setColor(ccc3(0, 255, 0));
    returnBtn->setPosition(ccp(mask->getContentSize().width / 2, mask->getContentSize().height * 0.3));
    
    CCMenu* menu = CCMenu::create(returnBtn, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    mask->addChild(menu);
}

void RichManPopLayer::backToModel() {
    RichManGameController_->resetData();
    GameUtil::RunScene(RICH_MAN_MODEL_CHOOSE);
}

void RichManPopLayer::countDown() {
    int timeLeft = std::atoi(countDonwLabel->getString());
    timeLeft -= 1;
    if (timeLeft < 0) {
        this->unscheduleAllSelectors();
        closeLayer();
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

void RichManPopLayer::makeGameBuildPop() {
    bg = CCSprite::create("popBg.png");
    bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(bg);
    
    setNode = CCNode::create();
    bg->addChild(setNode);
    
    float bgWidth = bg->getContentSize().width;
    float bgHeight = bg->getContentSize().height;
    
    CCLabelTTF* tips = CCLabelTTF::create("设置题库来狙击对手吧~", FONT_NAME, 15);
    tips->setColor(ccc3(0, 0, 0));
    tips->setPosition(ccp(bgWidth / 2, bgHeight * 0.7));
    bg->addChild(tips);
    
    if (RichManGameController_->getCurPlayerIsNPC()) {
        CCLabelTTF* npcTips = CCLabelTTF::create("", FONT_NAME, 15);
        npcTips->setColor(ccc3(255, 0, 0));
        npcTips->setPosition(ccp(bgWidth / 2, bgHeight / 2));
        bg->addChild(npcTips);
        if (arc4random() % 5 > 2 && RichManGameController_->getCurPlayerScore() > 50) { //npc随机设置题目
            RichManGameController_->setCurPlayerScore(-50);
            RichManGameController_->setQuestion(arc4random() % 2);
            npcTips->setString("一只鸡正在设置题目，请耐心等待");
        } else { //npc放弃
            npcTips->setString("一只鸡心情不好，放弃了设置");
        }
        
        npcTips->runAction(CCSequence::create(CCDelayTime::create(1),
                                              CCFadeOut::create(0.5f),
                                              CCFadeIn::create(0.5f),
                                              CCFadeOut::create(0.5f),
                                              CCFadeIn::create(0.5f),
                                              CCFadeOut::create(0.5f),
                                              CCFadeIn::create(0.5f),
                                              CCCallFunc::create(this, callfunc_selector(RichManPopLayer::closeLayer)),
                                              NULL));
        return;
    }
    
    myScore = CCLabelTTF::create(CCString::createWithFormat("我的学力:  %d", RichManGameController_->getCurPlayerScore())->getCString(), FONT_NAME, 15);
    myScore->setColor(ccc3(0,255, 0));
    myScore->setPosition(ccp(bgWidth / 2, bgHeight * 0.6));
    bg->addChild(myScore);
    
    CCMenuItemLabel* setBtn = CCMenuItemLabel::create(CCLabelTTF::create("设置题库", FONT_NAME, 20), this, menu_selector(RichManPopLayer::setQuestion));
    setBtn->setColor(ccc3(255, 0, 0));
    setBtn->setPosition(ccp(bgWidth * 0.3, bgHeight * 0.4));
    
    tips = CCLabelTTF::create("(需要消耗50学力哦)", FONT_NAME, 10);
    tips->setColor(ccc3(255, 0, 0));
    tips->setPosition(ccp(bgWidth * 0.3, bgHeight * 0.35));
    setNode->addChild(tips);
    
    CCMenuItemLabel* leaveBtn = CCMenuItemLabel::create(CCLabelTTF::create("先不设置", FONT_NAME, 20), this, menu_selector(RichManPopLayer::closeLayer));
    leaveBtn->setColor(ccc3(255, 0, 0));
    leaveBtn->setPosition(ccp(bgWidth * 0.7, bgHeight * 0.4));
    
    CCMenu* menu = CCMenu::create(setBtn, leaveBtn, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    setNode->addChild(menu);
}

void RichManPopLayer::setQuestion(CCObject *pSender, CCTouch *pTouch) {
    float bgWidth = bg->getContentSize().width;
    float bgHeight = bg->getContentSize().height;
    setNode->removeAllChildrenWithCleanup(true);
    if (RichManGameController_->getCurPlayerScore() <= 50) {
        CCLabelTTF* tips = CCLabelTTF::create("很遗憾，学力不够，下次再来吧", FONT_NAME, 15);
        tips->setColor(ccc3(255, 0, 0));
        tips->setPosition(ccp(bgWidth / 2, bgHeight * 0.5));
        setNode->addChild(tips);
        
        tips->runAction(CCSequence::create(CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCCallFunc::create(this, callfunc_selector(RichManPopLayer::closeLayer)),
                                           NULL));
        return;
    }
    
    if (layerType == GAME_CROSS) {
        CCLabelTTF* tips = CCLabelTTF::create("选择题库来升级吧~", FONT_NAME, 18);
        tips->setColor(ccc3(255, 215, 0));
        tips->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.5));
        setNode->addChild(tips);
    }
    
    CCMenuItemLabel* tangshi = CCMenuItemLabel::create(CCLabelTTF::create("唐诗赏析", FONT_NAME, 20), this, menu_selector(RichManPopLayer::setQuestionOver));
    tangshi->setTag(TANG_SHI);
    tangshi->setColor(ccc3(255, 0, 0));
    tangshi->setPosition(ccp(bgWidth * 0.3, bgHeight * 0.4));
    
    CCMenuItemLabel* songci = CCMenuItemLabel::create(CCLabelTTF::create("宋词赏析", FONT_NAME, 20), this, menu_selector(RichManPopLayer::setQuestionOver));
    songci->setTag(SONG_CI);
    songci->setColor(ccc3(255, 0, 0));
    songci->setPosition(ccp(bgWidth * 0.7, bgHeight * 0.4));
    
    CCMenu* menu = CCMenu::create(tangshi, songci, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    setNode->addChild(menu);
}

void RichManPopLayer::setQuestionOver(cocos2d::CCObject *pSender, cocos2d::CCTouch *pTouch) {
    float bgWidth = bg->getContentSize().width;
    float bgHeight = bg->getContentSize().height;
    RichManGameController_->setCurPlayerScore(-50);
    myScore->setString(CCString::createWithFormat("我的学力:  %d", RichManGameController_->getCurPlayerScore())->getCString());
    setNode->removeAllChildrenWithCleanup(true);
    int tag = dynamic_cast<CCNode*>(pSender)->getTag();
    Json::Value& settedQuestion = RichManGameController_->setQuestion(tag);
    
    if (layerType == GAME_CROSS) {
        CCLabelTTF* holdDetail = CCLabelTTF::create(CCString::createWithFormat("升级成功，当前题库等级%d", RichManGameController_->getCurHolderInfo()["questions"].size())->getCString(), FONT_NAME, 16);
        holdDetail->setColor(ccc3(0, 255, 0));
        holdDetail->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.6));
        setNode->addChild(holdDetail);
    }
    
    CCLabelTTF* tips = CCLabelTTF::create("您设置的题目是:" ,FONT_NAME, 15);
    tips->setColor(ccc3(0,0,0));
    tips->setPosition(ccp(bgWidth * 0.4, bgHeight * 0.5));
    setNode->addChild(tips);
    
    CCLabelTTF* up = CCLabelTTF::create(settedQuestion[0u].asCString() ,FONT_NAME, 18);
    up->setColor(ccc3(255,0,0));
    up->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.4));
    setNode->addChild(up);
    
    CCLabelTTF* down = CCLabelTTF::create(settedQuestion[1].asCString() ,FONT_NAME, 18);
    down->setColor(ccc3(255,0,0));
    down->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.3));
    setNode->addChild(down);
    
    CCMenuItemLabel* sureBtn = CCMenuItemLabel::create(CCLabelTTF::create("确定", FONT_NAME, 20), this, menu_selector(RichManPopLayer::closeLayer));
    sureBtn->setColor(ccc3(0, 0, 0));
    sureBtn->runAction(GameUtil::createHeartBeatAnimationAction());
    sureBtn->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.15));
    
    CCMenu* menu = CCMenu::create(sureBtn, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    setNode->addChild(menu);
}

void RichManPopLayer::makeGameCrossPop() {
    bg = CCSprite::create("popBg.png");
    bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(bg);
    
    setNode = CCNode::create();
    bg->addChild(setNode);
    
    curAnswer = "";
    
    float bgWidth = bg->getContentSize().width;
    float bgHeight = bg->getContentSize().height;
    
    Json::Value& holderInfo = RichManGameController_->getCurHolderInfo();
    int holderId = holderInfo["playerId"].asInt();
    const char* holderName = RichManGameController_->getPlayerName(holderId);
    Json::Value& questions = holderInfo["questions"];
    
    int curPlayerId = RichManGameController_->getCurPlayerId();
    if (holderId == curPlayerId) { //来到了自家地盘
        CCLabelTTF* tips = CCLabelTTF::create("我的地盘我做主!", FONT_NAME, 20);
        tips->setColor(ccc3(0, 0, 0));
        tips->setPosition(ccp(bgWidth / 2, bgHeight * 0.8));
        bg->addChild(tips);
        
        if (RichManGameController_->getCurPlayerIsNPC()) {
            CCLabelTTF* npcTips = CCLabelTTF::create("", FONT_NAME, 15);
            npcTips->setColor(ccc3(255, 0, 0));
            npcTips->setPosition(ccp(bgWidth / 2, bgHeight / 2));
            bg->addChild(npcTips);
            if (arc4random() % 5 > 2 && RichManGameController_->getCurPlayerScore() > 50) { //npc升级题库
                RichManGameController_->setCurPlayerScore(-50);
                RichManGameController_->setQuestion(arc4random() % 2);
                npcTips->setString("一只鸡正在升级题库，可要小心了");
            } else { //npc放弃
                npcTips->setString("一只鸡傻乎乎的放弃了升级题库");
            }
            
            npcTips->runAction(CCSequence::create(CCDelayTime::create(1),
                                                  CCFadeOut::create(0.5f),
                                                  CCFadeIn::create(0.5f),
                                                  CCFadeOut::create(0.5f),
                                                  CCFadeIn::create(0.5f),
                                                  CCFadeOut::create(0.5f),
                                                  CCFadeIn::create(0.5f),
                                                  CCCallFunc::create(this, callfunc_selector(RichManPopLayer::closeLayer)),
                                                  NULL));
            return;
        }
        
        myScore = CCLabelTTF::create(CCString::createWithFormat("我的学力:  %d", RichManGameController_->getCurPlayerScore())->getCString(), FONT_NAME, 15);
        myScore->setColor(ccc3(0,255, 0));
        myScore->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.7));
        bg->addChild(myScore);
        
        CCLabelTTF* holdDetail = CCLabelTTF::create(CCString::createWithFormat("当前题库等级%d", questions.size())->getCString(), FONT_NAME, 16);
        holdDetail->setColor(ccc3(0, 255, 0));
        holdDetail->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.6));
        setNode->addChild(holdDetail);
        
        CCMenuItemLabel* updateBtn = CCMenuItemLabel::create(CCLabelTTF::create("升级题库", FONT_NAME, 20), this, menu_selector(RichManPopLayer::setQuestion));
        updateBtn->setColor(ccc3(255, 0, 0));
        updateBtn->setPosition(ccp(bgWidth * 0.3, bgHeight * 0.4));
        
        tips = CCLabelTTF::create("(需要消耗50学力哦)", FONT_NAME, 10);
        tips->setColor(ccc3(255, 0, 0));
        tips->setPosition(ccp(bgWidth * 0.3, bgHeight * 0.35));
        setNode->addChild(tips);
        
        CCMenuItemLabel* leaveBtn = CCMenuItemLabel::create(CCLabelTTF::create("不升级了", FONT_NAME, 20), this, menu_selector(RichManPopLayer::closeLayer));
        leaveBtn->setColor(ccc3(255, 0, 0));
        leaveBtn->setPosition(ccp(bgWidth * 0.7, bgHeight * 0.4));
        
        CCMenu* menu = CCMenu::create(updateBtn, leaveBtn, NULL);
        menu->setTouchPriority(0);
        menu->setPosition(ccp(0, 0));
        setNode->addChild(menu);
    } else {
        CCLabelTTF* tips = CCLabelTTF::create(CCString::createWithFormat("艾玛，这是%s的地盘，我可不能丢了我的学力！", holderName)->getCString(), FONT_NAME, 16, CCSizeMake(bgWidth * 0.9, 0), kCCTextAlignmentCenter, kCCVerticalTextAlignmentTop);
        tips->setColor(ccc3(255, 0, 0));
        tips->setPosition(ccp(bgWidth / 2, bgHeight * 0.8));
        bg->addChild(tips);
        
        if (!RichManGameController_->getCurPlayerIsNPC()) { //非NPC
            showQuestion();
        } else { //NPC
            CCLabelTTF* holdDetail = CCLabelTTF::create(CCString::createWithFormat("当前题库等级%d", questions.size())->getCString(), FONT_NAME, 16);
            holdDetail->setColor(ccc3(255, 215, 0));
            holdDetail->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.6));
            setNode->addChild(holdDetail);
            
            tips = CCLabelTTF::create("一只鸡正在紧张的答题...", FONT_NAME, 16);
            tips->setColor(ccc3(0, 0, 0));
            tips->setPosition(ccp(bgWidth / 2, bgHeight / 2));
            setNode->addChild(tips);
            
            tips->runAction(CCSequence::create(CCDelayTime::create(3),
                                               CCFadeOut::create(0.5),
                                               CCFadeIn::create(0.5),
                                               CCFadeOut::create(0.5),
                                               CCFadeIn::create(0.5),
                                               CCCallFunc::create(this, callfunc_selector(RichManPopLayer::npcAnswerOver)),
                                               NULL));
        }
    }
}

void RichManPopLayer::reMakeGameBuildPop() {
    bg->removeFromParentAndCleanup(true);
    layerType = GAME_BUILD;
    RichManGameController_->freeHoldedBlock();
    makeGameBuildPop();
}

void RichManPopLayer::showQuestion() {
    float bgWidth = bg->getContentSize().width;
    float bgHeight = bg->getContentSize().height;
    setNode->removeAllChildrenWithCleanup(true);
    
    Json::Value& questions = RichManGameController_->getCurHolderInfo()["questions"];
    if (questions.size() == 0) { //全部答完
        CCLabelTTF* tips = CCLabelTTF::create("厉害，你答对了所有的题目，5秒后将有机会成为该地盘的主人哦", FONT_NAME, 14, CCSizeMake(bgWidth * 0.9, 0),kCCTextAlignmentCenter);
        tips->setColor(ccc3(0, 255, 0));
        tips->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.5));
        setNode->addChild(tips);
        
        tips->runAction(CCSequence::create(CCDelayTime::create(3),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCCallFunc::create(this, callfunc_selector(RichManPopLayer::reMakeGameBuildPop)),
                                           NULL));
        return;
    }
    CCLabelTTF* holdDetail = CCLabelTTF::create(CCString::createWithFormat("当前题库等级%d", questions.size())->getCString(), FONT_NAME, 16);
    holdDetail->setColor(ccc3(255, 215, 0));
    holdDetail->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.6));
    setNode->addChild(holdDetail);
    
    CCLabelTTF* tips = CCLabelTTF::create("请写出下一句:", FONT_NAME, 14);
    tips->setColor(ccc3(0, 0, 0));
    tips->setPosition(ccp(bgWidth * 0.3, bgHeight * 0.5));
    setNode->addChild(tips);
    
    curQuestion = questions[questions.size() - 1];
    CCLabelTTF* up = CCLabelTTF::create(curQuestion[0u].asCString(), FONT_NAME, 17);
    up->setColor(ccc3(255, 215, 0));
    up->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.4));
    setNode->addChild(up);
    
    CCScale9Sprite *editboxBg = CCScale9Sprite::create("InputBg.png");
    CCEditBox* editbox = CCEditBox::create(CCSprite::create("InputBg.png")->getContentSize(), editboxBg);
    editbox->setTouchPriority(getTouchPriority());
    editbox->setFontName(FONT_NAME);
    editbox->setFontColor(ccc3(255,215,0));
    editbox->setFontSize(17);
    editbox->setInputMode(kEditBoxInputModeAny);
    editbox->setDelegate(this);
    editbox->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.3));
    editbox->setPlaceholderFontName(FONT_NAME);
    editbox->setPlaceHolder("请填写正确答案");
    editbox->setPlaceholderFontColor(ccc3(255, 215, 0));
    setNode->addChild(editbox);
    
    CCMenuItemLabel* submitBtn = CCMenuItemLabel::create(CCLabelTTF::create("提交答案", FONT_NAME, 18), this, menu_selector(RichManPopLayer::submitAnswer));
    submitBtn->setColor(ccc3(0, 255, 0));
    submitBtn->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.15));
    
    CCMenu* menu = CCMenu::create(submitBtn, NULL);
    menu->setTouchPriority(0);
    menu->setPosition(ccp(0, 0));
    setNode->addChild(menu);
}

void RichManPopLayer::npcAnswerOver() {
    float bgWidth = bg->getContentSize().width;
    float bgHeight = bg->getContentSize().height;
    setNode->removeAllChildrenWithCleanup(true);
    Json::Value& questions = RichManGameController_->getCurHolderInfo()["questions"];
    int answered = 0;
    int questionsSize = questions.size();
    for (int i = 0; i < questionsSize; i++) {
        if (arc4random() % 5 > 2) { //答对
            answered++;
        } else {
            break;
        }
    }
    const char* result = "";
    if (answered == 0) { //npc 一题没答对
        result = "一只鸡真笨，第一个题目就错了，失去了30学力";
        RichManGameController_->answerWrong();
    } else if (answered < questionsSize) { //没有全部答对
        result = CCString::createWithFormat("一只鸡还是可以的，答对了%d道题目，但是还是失去了30学力", answered)->getCString();
        RichManGameController_->reduceHolderQuestions(answered);
        RichManGameController_->answerWrong();
        
        CCLabelTTF* holdDetail = CCLabelTTF::create(CCString::createWithFormat("当前题库等级%d", questionsSize - answered)->getCString(), FONT_NAME, 16);
        holdDetail->setColor(ccc3(0, 255, 0));
        holdDetail->setPosition(ccp(bgWidth * 0.5, bgHeight * 0.7));
        setNode->addChild(holdDetail);
    } else { //全部答对
        if (arc4random() % 5 > 2 && RichManGameController_->getCurPlayerScore() > 50) { //npc随机设置题目
            result = "天啊，一只鸡答对了所有题目，并且霸占了此地，正在设置题目，555...";
            RichManGameController_->setCurPlayerScore(-50);
            RichManGameController_->grabHolder(arc4random() % 2);
        } else { //npc放弃
            result = "天啊，一只鸡答对了所有题目，上帝保佑，他放弃了占领该地盘";
            RichManGameController_->freeHoldedBlock();
        }
    }
    
    CCLabelTTF* tips = CCLabelTTF::create(result, FONT_NAME, 15, CCSizeMake(bgWidth * 0.9, 0),kCCTextAlignmentCenter);
    tips->setColor(ccc3(0, 0, 0));
    tips->setPosition(ccp(bgWidth / 2, bgHeight / 2));
    setNode->addChild(tips);
    
    tips->runAction(CCSequence::create(CCDelayTime::create(3),
                                       CCFadeOut::create(0.5),
                                       CCFadeIn::create(0.5),
                                       CCFadeOut::create(0.5),
                                       CCFadeIn::create(0.5),
                                       CCFadeOut::create(0.5),
                                       CCFadeIn::create(0.5),
                                       CCCallFunc::create(this, callfunc_selector(RichManPopLayer::closeLayer)),
                                       NULL));
}

void RichManPopLayer::submitAnswer() {
    float bgWidth = bg->getContentSize().width;
    float bgHeight = bg->getContentSize().height;
    setNode->removeAllChildrenWithCleanup(true);
    if (std::strcmp(curAnswer.c_str(), curQuestion[1].asCString()) != 0) { //答错了
        RichManGameController_->answerWrong();
        CCLabelTTF* tips = CCLabelTTF::create("很遗憾，没能答对题目，损失30学力", FONT_NAME, 14);
        tips->setColor(ccc3(255, 0, 0));
        tips->setPosition(ccp(bgWidth / 2, bgHeight / 2));
        setNode->addChild(tips);
        
        tips->runAction(CCSequence::create(CCDelayTime::create(1),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCCallFunc::create(this, callfunc_selector(RichManPopLayer::closeLayer)),
                                           NULL));
    } else {
        RichManGameController_->reduceHolderQuestions(1);
        CCLabelTTF* tips = CCLabelTTF::create("恭喜你答对了，请等待下一题", FONT_NAME, 14);
        tips->setColor(ccc3(0, 255, 0));
        tips->setPosition(ccp(bgWidth / 2, bgHeight / 2));
        setNode->addChild(tips);
        
        tips->runAction(CCSequence::create(CCDelayTime::create(1),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCFadeOut::create(0.5),
                                           CCFadeIn::create(0.5),
                                           CCCallFunc::create(this, callfunc_selector(RichManPopLayer::showQuestion)),
                                           NULL));
    }
}

void RichManPopLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
    
}

void RichManPopLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text) {
    
}

void RichManPopLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    
}

void RichManPopLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    curAnswer = editBox->getText();
}

void RichManPopLayer::closeLayer() {
    this->removeFromParentAndCleanup(true);
    switch (layerType) {
        case GAME_FORWARD:
            RichManGameController_->move();
            break;
        case GAME_BUILD:
        case GAME_CROSS:
        case GAME_RANDOM:
        case GAME_SHOP:
            RichManGameController_->next();
            break;
    }
}
