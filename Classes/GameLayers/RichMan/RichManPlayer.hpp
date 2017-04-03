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
    void initWithDatas(const char* modelName, bool isNeedFlip, bool isNPC, int playerId);
    void turnToForward();
    void forwardBtnDown(CCObject *pSender, CCTouch *pTouch);
    void makeForwardLayer();
    int getCurBlocks();
    void setCurBlocks(int blocks);
    void move(CCSequence* actSequence);
    int getScore();
    void setScore(int scoreDelta);
    bool isPlayer2();
    bool getIsNPC();
    int getPlayerId();
    void setRestRound(int restRounds);
    void makeCommonTips(const char* tips);
    void restOver();
private:
    int score;
    int playerId;
    bool isNPC;
    HeroModel* hModel;
    CCSize winSize;
    CCMenuItemLabel* forwardBtn;
    int curBlocks;
    CCSprite* movePic;
    CCLabelTTF* commonTips;
    CCLabelTTF* scoreLabel;
    int restRounds;
};

#endif /* RichManPlayer_hpp */
