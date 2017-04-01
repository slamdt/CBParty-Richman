//
//  RichManPlayer.hpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/3/31.
//
//

#ifndef RichManPlayer_hpp
#define RichManPlayer_hpp

#include "GameUtil.h"
#include "HeroModel.h"

class RichManPlayer : public CCNode {
public:
    CREATE_FUNC(RichManPlayer)
    virtual bool init();
    void initWithDatas(const char* modelName, bool isNeedFlip, bool isNPC = false);
    void turnToForward(bool isNPC);
    void forwardBtnDown(CCObject *pSender, CCTouch *pTouch);
    void makeForwardLayer();
    int getCurBlocks();
    void setCurBlocks(int blocks);
    void move(CCSequence* actSequence);
private:
    int score;
    HeroModel* hModel;
    CCSize winSize;
    CCMenuItemLabel* forwardBtn;
    int curBlocks;
    CCSprite* movePic;
};

#endif /* RichManPlayer_hpp */
