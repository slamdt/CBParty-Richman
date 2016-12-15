//
//  HeroModel.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#include "HeroModel.h"

void HeroModel::AddArmatureInfo() {
    cocos2d::CCString* cczName = cocos2d::CCString::createWithFormat("%s.pvr.ccz",_modelName);
    cocos2d::CCString* plistName = cocos2d::CCString::createWithFormat("%s.plist",_modelName);
    cocos2d::CCString* xmlName = cocos2d::CCString::createWithFormat("%s.xml",_modelName);
    cocos2d::extension::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(cczName->getCString(),plistName->getCString(),xmlName->getCString());
    
    m_pAnimator = cocos2d::extension::CCArmature::create(_modelName);
    if (_isNeedFlip) {
        m_pAnimator->setScaleX(-m_pAnimator->getScaleX());
    }
    this->addChild(m_pAnimator);
}

HeroModel* HeroModel::Create(const char *modelName,bool isNeedFlip) {
    HeroModel *hero = new HeroModel(modelName,isNeedFlip);
    hero->AddArmatureInfo();
    hero->autorelease();
    return hero;
}

float HeroModel::GetHeight() {
    return m_pAnimator->getContentSize().height*m_pAnimator->getScaleY();
}

void HeroModel::PlayAnimation(const char *aniName) {
    m_pAnimator->getAnimation()->play(aniName);
}