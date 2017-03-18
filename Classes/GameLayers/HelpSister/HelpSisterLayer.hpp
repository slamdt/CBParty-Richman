//
//  HelpSisterLayer.hpp
//  DoTaBattle
//
//  Created by yuyu on 17/1/11.
//
//

#ifndef HelpSisterLayer_hpp
#define HelpSisterLayer_hpp

#include "BaseLayer.h"
enum LayerType{
    LOGIN_LAYER = 1,
    REGISIST_LAYER,
    PLAY_LAYER
};

enum EditType {
    ACCOUNT = 1,
    PASSWORD
};

typedef struct PLAYER{
    std::string account;
    std::string password;
    int score;
} player;
class HelpSisterLayer : public BaseLayer,public CCEditBoxDelegate {
public:
    CREATE_FUNC(HelpSisterLayer)
    virtual bool init();
    void makeLayerByType(LayerType type);
    void showLogin();
    void startLogin(CCObject* pSender, CCTouch* ptouch);
    void startRegisit(CCObject* pSender, CCTouch* ptouch);
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
    
    bool checkLogin();
private:
    CCNode* layerNode;
    CCSize winSize;
    std::string accountStr;
    std::string passwordStr;
    std::vector<player> players;
};

#endif /* HelpSisterLayer_hpp */
