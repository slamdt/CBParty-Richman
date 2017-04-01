//
//  tinyxmlHellp.h
//  WestWar
//
//  Created by ZhenGuo Li on 12-10-31.
//
//

#ifndef __WestWar__tinyxmlHellp__
#define __WestWar__tinyxmlHellp__

#include "tinystr.h"
#include "tinyxml.h"
#include "json.h"
#include "cocos2d.h"
using namespace cocos2d;
class tinyxmlHellp 
{
public:
    
    static const char * gainValue(TiXmlDocument *myDocument,const char * PersonName,const char *searchID,const char *searchValue,const char * targetID);
    
    static int gainIntValue(TiXmlDocument *myDocument,const char * PersonName,const char *searchID,const char *searchValue,const char * targetID);
    
    static TiXmlElement * gainElementByDoc(TiXmlDocument *myDocument,const char * PersonName);
    
    static TiXmlElement * gainElementBychild(TiXmlElement *Parent,const char * PersonName);
    
    static TiXmlElement * gainElementByType(TiXmlElement *Element,const char * searchID,const char *searchValue);
    
    static const char * gainValueByElement(TiXmlElement *Element,const char * TypeID);
    
    static int gainValueByChar(const char * _char);
    
    static int gainIntByKEY(TiXmlElement *Element,const char * KEY);
    
    static double gainDoubleByKEY(TiXmlElement *Element,const char * KEY);
    
    static TiXmlElement * gainElementByType(TiXmlElement *Element,const char * searchID1,const char *searchValue1,const char * searchID2,const char *searchValue2,const char * searchID3,const char *searchValue3);
    
    static TiXmlElement * gainElementByType(TiXmlElement *Element,const char * searchID1,const char *searchValue1,const char * searchID2,const char *searchValue2);
    
    static Json::Value gainIntJsonByChar(const char *_input);
    
    static Json::Value gainCharJsonByChar(const char *_input);
    
    static CCSpriteFrame * gainSpriteFrameByImg(const char * _img);
    
    static const char * gainValueByElementName(TiXmlElement *Element,const char * ElementName);
//    static const char * gainValueByElementNameFormat(TiXmlElement *Element,const char* format, ...);
//    static bool isTouchOnSprite(CCNode * sprite,CCTouch *pTouch);
    
    //尝试得到含中文字符串长度
    
};


#endif /* defined(__WestWar__tinyxmlHellp__) */
