//
//  RichManModelChooseLayer.hpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/4/3.
//
//

#ifndef RichManModelChooseLayer_hpp
#define RichManModelChooseLayer_hpp

#include "BaseLayer.h"

class RichManModelChooseLayer : public BaseLayer, public CCEditBoxDelegate{
public:
    CREATE_FUNC(RichManModelChooseLayer)
    virtual bool init();
    
    void chooseModel(CCObject *pSender, CCTouch *pTouch);
    void beginGame();
    
    CCEditBox* createEditBox(int tag);
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(CCEditBox* editBox);
private:
    CCNode* node;
};

#endif /* RichManModelChooseLayer_hpp */
