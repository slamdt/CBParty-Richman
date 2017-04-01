//
//  HeroModel.h
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#ifndef __DoTaBattle__HeroModel__
#define __DoTaBattle__HeroModel__

#include "GameUtil.h"
#include "CCArmatureDataManager.h"
#include "CCArmature.h"

class HeroModel : public cocos2d::CCNodeRGBA {
public:
    HeroModel(const char* modelName,bool isNeedFlip) :_modelName(modelName),_isNeedFlip(isNeedFlip) {
        
    }
    static HeroModel* Create(const char* modelName,bool isNeedFlip);
    void AddArmatureInfo();
    void PlayAnimation(const char* aniName);
    float GetHeight();
    float GetWidth();
    std::string GetResoucePrePath(const char* modelName);
private:
    const char * _modelName;
    bool _isNeedFlip;
    cocos2d::extension::CCArmature* m_pAnimator;
};

#endif /* defined(__DoTaBattle__HeroModel__) */
