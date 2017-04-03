//
//  RichManPopLayer.hpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/4/1.
//
//

#ifndef RichManPopLayer_hpp
#define RichManPopLayer_hpp

#include "BaseLayer.h"

class RichManPopLayer : public BaseLayer, public CCEditBoxDelegate{
public:
    CREATE_FUNC(RichManPopLayer)
    virtual bool init();
    void makeContentWithType(int type);
    void countDown();
    void makeForwardBlocks();
    void forwardOver();
    void makeGameBuildPop();
    void setQuestion(CCObject *pSender, CCTouch *pTouch);
    void setQuestionOver(CCObject *pSender, CCTouch *pTouch);
    void makeGameCrossPop();
    void reMakeGameBuildPop();
    void npcAnswerOver();
    void submitAnswer();
    void showQuestion();
    void showGameOver(int loserId);
    void closeLayer();
    void backToModel();
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
    
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent) {return true;}
private:
    int layerType;
    CCLabelTTF* countDonwLabel; //倒计时pop
    BoFlash* fowardFlash; //摇骰子pop
    CCNode* setNode; //设置题库
    CCSprite* bg;
    CCLabelTTF* myScore; //我的学力
    Json::Value curQuestion;
    std::string curAnswer;
};

#endif /* RichManPopLayer_hpp */
