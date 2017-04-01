//
//  BSFlash.cpp
//  MassBrawl
//
//  Created by xu ning on 12-12-7.
//
//

#include "BoFlash.h"
//#include "CConnectionData.h"
#include "SPArmatureDataManager.h"
#include "SPBatchNodeManager.h"


/**
 * xml文件池
 */
static CCArray* xmls = NULL;
/**
 * 析构
 */
BoFlash::~BoFlash()
{
    if (xmls != NULL)
    {
//        xmls->release();
//        xmls=NULL;
    }
    ArmatureArray->release();
}

/**
 * 创建一个对象
 */
BoFlash* BoFlash::create(const char* plist, const char* png, const char* xml, const char* name, bool selfScheduleUpdate, const char* defaultAction){
    BoFlash *pSprite = new BoFlash();
    if (pSprite && pSprite->init(plist, png, xml, name, selfScheduleUpdate, defaultAction))
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

/**
 * 创建一个对象
 */
BoFlash *BoFlash::create(const char *name)
{
    BoFlash *pSprite = new BoFlash();
    const char *plistName = CCString::createWithFormat("%s.plist",name)->getCString();
    const char *pngName = CCString::createWithFormat("%s.png",name)->getCString();
    const char *xmlName = CCString::createWithFormat("%s.xml",name)->getCString();
    if (pSprite && pSprite->init(plistName, pngName, xmlName, name, true, NULL))
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

/**
 * 初始化
 */
bool BoFlash::init(const char* plist, const char* png, const char* xml, const char* name, bool selfScheduleUpdate, const char* defaultAction){
    bool success = CCSprite::init();
    
//    // 得到新的xml列表
//    if (xmls == NULL) {
//        xmls = CCArray::create();
//        xmls->retain();
//    }
//    // 添加新的xml
//    bool hasXml = false;
//    for (int i = 0; i < xmls->count(); i++) {
//        CCString* tmp = (CCString*)xmls->objectAtIndex(i);
//        if (tmp->isEqual(CCString::create(xml)) == true) {
//            hasXml = true;
//            break;
//        }
//    }
//    if (hasXml == false) {
//        CCConnectionData::sharedConnectionData()->addData(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(xml));
//        xmls->addObject(CCString::create(xml));
//    }
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, png);
//    CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create(png);
//    armature = CCArmature::create(name, name, batchNode);
//    armature->getDisplay()->setPosition(ccp(0, 0));
//    armature->getDisplay()->setScale( 1 );
//    if (animationListener == NULL) {
//        armature->getAnimation()->setAniEventListener(this);
//    }
//    else{
//        armature->getAnimation()->setAniEventListener(animationListener);
//    }
//    
//    addChild( batchNode );
//    
//    if (selfScheduleUpdate == true) {
//        scheduleUpdate();
//    }
    ArmatureArray = new CCArray();
    
    ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(name, "", png, plist, xml);
    //2013318
    CCLog("ArmatureDataManager create %s", name);
    Sparmature = Armature::create(name);
    Sparmature->setAnimationCallback(this);
    Sparmature->setPosition(0,0);
    ArmatureArray->addObject(Sparmature);
    addChild(Sparmature->getDisPlayBatchNode());
    if (defaultAction != NULL)
    {
        playTo(defaultAction);
    }
    
    scheduleUpdate();
    
    
    return success;
}


/**
 * 改变动作
 */
void BoFlash::playTo(const char* action,bool loop)
{
    if (Sparmature->getAnimation() == NULL || Sparmature == NULL) return;
    
//    armature->getAnimation()->playTo((void*)action, -1, -1, loop);
//    armature->update(0.1);
    
    //2013318
    Sparmature->getAnimation()->setLoop(1);
    Sparmature->getAnimation()->play(action);
    Sparmature->getAnimation()->setLoop(loop);
    Sparmature->update(0.1);
}
/**
 * 改变动作
 */
void BoFlash::playTo(const char* action){
    if (Sparmature->getAnimation() == NULL || Sparmature == NULL) return;
    
//    armature->setVisible(true);
//    armature->getAnimation()->playTo((void*)action, -1, -1, true);
//    armature->update(0.1);
    
    //2013318
    Sparmature->getAnimation()->setLoop(1);
    Sparmature->getAnimation()->play(action);
    Sparmature->update(0.1);
}

/**
 * 得到当前动作
 */
const char *BoFlash::getCurrActionID()
{
//    return armature->getAnimation()->mAniIDNow;
    
    std::string MovmentName = Sparmature->getAnimation()->getMovmentNames()[0];
    return MovmentName.c_str();
}

/**
 * 返回方法
 */
void BoFlash::returnFunc(CCActionInstant *Func ,bool isRepeat)
{
    if (isRepeat) return;
//    armature->getAnimation()->isRepeat_ = !isRepeat;
    //2013318
    Sparmature->getAnimation()->setLoop(isRepeat);
    Func_ = Func;
    Func_->retain();
}

//新1.4 动作回调
void BoFlash::onMovementEvent(Armature *_armature, const char *_eventType, const char *_movementID)
{
    std::string typesStr = _eventType;
    if (typesStr.compare(LOOP_COMPLETE) == 0)
	{
        if (Func_!=NULL) {
            runAction(Func_);
            Func_->release();
            Func_ = NULL;
        }
    }
    return;
}
/**
 * 动作回调
 */
void BoFlash::animationHandler(const char* status, const char* action, const char* frameID, bool isOpenFunc){
    //    CCLog("%s, %s, %s", status, action, frameID);
    if (isOpenFunc)
    {
        if (CCString::create(status)->isEqual(CCString::create("loopComplete")) && Func_ != NULL)
        {
            this->runAction(Func_);
//            armature->getAnimation()->isRepeat_ = false;
            return;
        }
    }
    
    //    if (CCString::create(status)->isEqual(CCString::create("loopComplete")))
    //    {
    //        if (CCString::create(action)->isEqual(CCString::create("stay")) == true) {
    //            playTo("move");
    //        }
    //        if (CCString::create(action)->isEqual(CCString::create("move")) == true) {
    //            playTo("attackStay");
    //        }
    //        if (CCString::create(action)->isEqual(CCString::create("attackStay")) == true) {
    //            playTo("attack");
    //        }
    //        if (CCString::create(action)->isEqual(CCString::create("attack")) == true) {
    //            playTo("beAttack");
    //        }
    //        if (CCString::create(action)->isEqual(CCString::create("beAttack")) == true) {
    //            playTo("win");
    //        }
    //        if (CCString::create(action)->isEqual(CCString::create("win")) == true) {
    //            playTo("stay");
    //        }
    //    }
    
}

void BoFlash::onEnter()
{
    CCSprite::onEnter();
}

void BoFlash::onExit()
{
    if (Func_!=NULL)
    {
        Func_->release();
    }
    CCSprite::onExit();
}

/**
 * 重写Update
 */
void BoFlash::update(float dt)
{
    CCObject::update(dt);
//    armature->update(dt);
    //2013318
    Sparmature->update(dt);
}