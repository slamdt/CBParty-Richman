//
//  BaseLayer.h
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#ifndef __DoTaBattle__BaseLayer__
#define __DoTaBattle__BaseLayer__

#include "GameUtil.h"

class BaseLayer : public CCLayer {
    CC_SYNTHESIZE(int, _touchPriority, TouchPriority)
    CC_SYNTHESIZE(bool, _isSwallowTouch, IsSwallowTouch)
public:
    BaseLayer() : _touchPriority(0),_isSwallowTouch(false) {
        
    }
    virtual bool init();
    
    // 覆盖CCLayer实现，注册触摸事件派发器
    virtual void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, _touchPriority, _isSwallowTouch);
    }
    
    // 覆盖CCLayer缺省实现，默认不捕获触摸点
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent){return false;}
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent){}
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent){}
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent){}
private:
    
};

#endif /* defined(__DoTaBattle__BaseLayer__) */
