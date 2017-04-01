//
//  BSFlash.h
//  MassBrawl
//
//  Created by xu ning on 12-12-7.
//
//

#ifndef __MassBrawl__BoFlash__
#define __MassBrawl__BoFlash__

#include <iostream>
#include "cocos2d.h"
//#include "CArmature.h"
#include "SPArmature.h"
using namespace cocos2d;
using namespace SPII;
using namespace SPII::SPArmature;

/*
 * 播放Flash时间线动画，XML格式
 */
class BoFlash : public CCSprite,public ArmatureAnimationCallback
{
    
public:
    /**
     * 创建一个对象,
     *  plist(plist文件名)
     *  png(图片名)
     *  xml(xml文件名)
     *  name(动作原件名)
     *  selfScheduleUpdate(是否需要自身推动动画播放,如果是true则会自己推动动画向前播放,如果是false则需要外部调用update(float dt)方法才会将动画推进一帧)
     *  defaultAction(默认动作的名字)
     *  animationListener(动作回调函数，在动作开始播放，结束播放，一个循环播放完都会调用这个监听器，如果监听器为NULL则会使用内部监听器，开发者也可以通过重写本类animationHandler方法来得到回调)
     */
    static BoFlash* create(const char* plist, const char* png, const char* xml, const char* name, bool selfScheduleUpdate, const char* defaultAction);
    
    static BoFlash *create(const char *name);
    
    /**
     * 改变动作
     */
    virtual void playTo(const char* action);
    
    /**
     * 改变动作
     */
    virtual void playTo(const char* action,bool loop);
    
    /**
     * 动作回调
     */
    virtual void animationHandler(const char* status, const char* action, const char* frameID,bool isOpenFunc);
    //新1.4 动作回调
    void onMovementEvent(Armature *_armature, const char *_eventType, const char *_movementID);
    
    /**
     * 重写Update
     */
    virtual void update(float dt);
    
    
    // 得到当前动作
    const char *getCurrActionID();
    
public:
    /**
     * 动画控制
     */
    //    CCArmature *armature;
    virtual void onEnter();
    virtual void onExit();
    
    CCArray *ArmatureArray;
    
    Armature *Sparmature;
    
    // 返回
    CCAction *Func_;
    
    // 返回方法
    void returnFunc(CCActionInstant *Func, bool isRepeat);
    
    // 析构
    virtual ~BoFlash(void);
    
    /**
     * 初始化
     */
    bool init(const char* plist, const char* png, const char* xml, const char* name, bool selfScheduleUpdate, const char* defaultAction);
};

#endif /* defined(__MassBrawl__BSFlash__) */
