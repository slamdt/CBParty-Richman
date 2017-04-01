//
//  HeroModel.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#include "HeroModel.h"

std::string HeroModel::GetResoucePrePath(const char *modelName) {
    std::string prePath = "Actor/";
    prePath += modelName;
    return prePath;
}

void HeroModel::AddArmatureInfo() {
    std::string sourcePrePath;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    sourcePrePath = _modelName;
#else
    sourcePrePath = GetResoucePrePath(_modelName) + "/" + _modelName;
#endif
    std::string cczName = sourcePrePath + ".pvr.ccz";
    std::string plistName = sourcePrePath + ".plist";
    std::string xmlName = sourcePrePath + ".xml";
    cocos2d::extension::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(cczName.c_str(),plistName.c_str(),xmlName.c_str());
    
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
    return m_pAnimator->getContentSize().height * m_pAnimator->getScaleY();
}

float HeroModel::GetWidth() {
    return m_pAnimator->getContentSize().width * m_pAnimator->getScaleX();
}

void HeroModel::PlayAnimation(const char *aniName) {
    m_pAnimator->getAnimation()->play(aniName);
}
