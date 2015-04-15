//
//  DoTaBattleAppDelegate.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-3-18.
//  Copyright __MyCompanyName__ 2015年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "CCDataReaderHelper.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEglView = CCEGLView::sharedOpenGLView();
    
    //===================多分辨率处理========================
    pDirector->setOpenGLView(pEglView);
    pDirector->setContentScaleFactor(2);
    cocos2d::extension::CCDataReaderHelper::setPositionReadScale(1.0f/pDirector->getContentScaleFactor());
    
    CCSize winSize = pDirector->getWinSize();
    CCLOG("original frame size:%f, %f", pEglView->getFrameSize().width, pEglView->getFrameSize().height);
    CCLOG("winsize is : %f,%f",winSize.width,winSize.height);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (getTargetPlatform()== kTargetIpad) {
        pEglView->setDesignResolutionSize(480, 320, kResolutionShowAll);
        
    } else {
        if(pEglView->getFrameSize().width == 1136) {
            pEglView->setDesignResolutionSize(568, 320, kResolutionShowAll);
        }
        else {
            pEglView->setDesignResolutionSize(480, 320, kResolutionShowAll);
        }
    }
#endif
    CCLOG("new frame size:%f, %f", CCEGLView::sharedOpenGLView()->getFrameSize().width, CCEGLView::sharedOpenGLView()->getFrameSize().height);

    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    CCDirector::sharedDirector()->setDepthTest(false);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *scene = GameLayer::scene();
    pDirector->runWithScene(scene);
    
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
