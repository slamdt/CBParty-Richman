//
//  tinyxmlHellp.cpp
//  WestWar
//
//  Created by ZhenGuo Li on 12-10-31.
//
//

#include "tinyxmlHellp.h"
#include "cocos2d.h"
using namespace cocos2d;


const char* tinyxmlHellp::gainValue(TiXmlDocument *myDocument,const char * PersonName,const char *searchID,const char *searchValue,const char * targetID)
{
    TiXmlElement *person = gainElementByDoc(myDocument, PersonName);
    TiXmlElement *targetPos = gainElementByType(person, searchID, searchValue);
    return gainValueByElement(targetPos, targetID);
}
int tinyxmlHellp::gainIntValue(TiXmlDocument *myDocument,const char * PersonName,const char *searchID,const char *searchValue,const char * targetID)
{
    return gainValueByChar(gainValue(myDocument, PersonName, searchID, searchValue, targetID));
}
TiXmlElement * tinyxmlHellp::gainElementByDoc(TiXmlDocument *myDocument,const char * PersonName)
{
    //获得根元素，即root。
    TiXmlElement *RootElement = myDocument->RootElement();
    if (strcmp(RootElement->Value(), PersonName)==0) {
        return RootElement;
    }
    else
    {
        return gainElementBychild(RootElement, PersonName);
    }
}
TiXmlElement * tinyxmlHellp::gainElementBychild(TiXmlElement *Parent,const char * PersonName)
{
    TiXmlElement *child = Parent->FirstChildElement();
    while (child!=NULL&&child->Value()!=NULL) {
        if (strcmp(child->Value(), PersonName)==0)
        {
            return child;
        }
        else
        {
            TiXmlElement *returnChild = gainElementBychild(child, PersonName);
            if(returnChild!=NULL)
            {
                return returnChild;
            }
            else
            {
                child = child->NextSiblingElement();
            }
        }
    }
    return NULL;
}
TiXmlElement * tinyxmlHellp::gainElementByType(TiXmlElement *Element,const char * searchID,const char *searchValue)
{
    TiXmlElement *child = Element->FirstChildElement();
    while (child!=NULL) {
        if (strcmp(gainValueByElement(child, searchID), searchValue)==0)
        {
            return child;
        }
        else
        {
            child = child->NextSiblingElement();
        }
    }
    return NULL;
}
TiXmlElement * tinyxmlHellp::gainElementByType(TiXmlElement *Element,const char * searchID1,const char *searchValue1,const char * searchID2,const char *searchValue2,const char * searchID3,const char *searchValue3)
{
    TiXmlElement *child = Element->FirstChildElement();
    while (child!=NULL) {
        if (strcmp(gainValueByElement(child, searchID1), searchValue1)==0&&strcmp(gainValueByElement(child, searchID2), searchValue2)==0&&strcmp(gainValueByElement(child, searchID3), searchValue3)==0)
        {
            return child;
        }
        else
        {
            child = child->NextSiblingElement();
        }
    }
    return NULL;
}
TiXmlElement * tinyxmlHellp::gainElementByType(TiXmlElement *Element,const char * searchID1,const char *searchValue1,const char * searchID2,const char *searchValue2)
{
    TiXmlElement *child = Element->FirstChildElement();
    while (child!=NULL) {
        if (strcmp(gainValueByElement(child, searchID1), searchValue1)==0&&strcmp(gainValueByElement(child, searchID2), searchValue2)==0)
        {
            return child;
        }
        else
        {
            child = child->NextSiblingElement();
        }
    }
    return NULL;
}
const char * tinyxmlHellp::gainValueByElement(TiXmlElement *Element,const char * TypeID)
{
    TiXmlAttribute *ID = Element->FirstAttribute();
    while (ID!=NULL) {
        if (strcmp(ID->Name(), TypeID)==0)
        {
            return ID->Value();
        }
        else
        {
            ID = ID->Next();
        }
    }
    return NULL;
}
double tinyxmlHellp::gainDoubleByKEY(TiXmlElement *Element,const char * KEY)
{
    return atof(gainValueByElement(Element, KEY));
}
int tinyxmlHellp::gainIntByKEY(TiXmlElement *Element,const char * KEY)
{
    return gainValueByChar(gainValueByElement(Element, KEY));
}
int tinyxmlHellp::gainValueByChar(const char * _char)
{
    return gainIntJsonByChar(_char)[unsigned(0)]["value0"].asInt();
}

Json::Value tinyxmlHellp::gainIntJsonByChar(const char *_input)
{
    int start = 0,json_state = 0,i = 0,numState = 0;
    Json::Value jsonInfo;
    while (true) {
        if(start==strlen(_input))
        {
            jsonInfo[i]["valueNum"] = json_state + 1;
            i++;
            numState = 0;
            break;
        }
        else if (_input[start] !=',' &&_input[start] !=';' &&_input[start] !='_')
        {
            CCString *typeStr = CCString::createWithFormat("value%d",json_state);
            if (_input[start] =='-')
            {
                numState = -1;
            }
            else
            {
                if (numState == 0)
                {
                    numState = 1;
                }
                
                jsonInfo[i][typeStr->getCString()] = jsonInfo[i][typeStr->getCString()].asInt()*10 + (_input[start] - '0')*numState;
                typeStr->release();
            }
            
        }
        else if (_input[start] ==',')
        {
            json_state ++;
            numState= 0;
        }
        else if (_input[start] ==';')
        {
            jsonInfo[i]["valueNum"] = json_state + 1;
            i++;
            json_state = 0;
            numState = 0;
        }
        else if (_input[start] =='_')
        {
            json_state ++;
            numState= 0;
        }
        start++;
    }
    if (strlen(_input)==0)
    {
        jsonInfo[unsigned(0)]["infoNum"] = 0;
        jsonInfo[unsigned(0)]["value0"] = 0;
    }
    else
    {
        jsonInfo[unsigned(0)]["infoNum"] = i;
    }
    return jsonInfo;
}

Json::Value tinyxmlHellp::gainCharJsonByChar(const char *_input)
{
    int start = 0,json_state = 0,i = 0;
    bool fisrt = true;
    Json::Value jsonInfo;
    jsonInfo.clear();
    while (true) {
        if(start==strlen(_input))
        {
            jsonInfo[i]["valueNum"] = json_state + 1;
            i++;
            break;
        }
        else if (_input[start] !=',' &&_input[start] !=';')
        {
            CCString *typeStr = CCString::createWithFormat("value%d",json_state);
            
            if (!fisrt) {
                jsonInfo[i][typeStr->getCString()] =
                CCString::createWithFormat("%s%c",jsonInfo[i][typeStr->getCString()].asCString(),_input[start])->getCString();
            }
            else
            {
                jsonInfo[i][typeStr->getCString()] =
                CCString::createWithFormat("%c",_input[start])->getCString();
            }
            typeStr->release();
            fisrt = false;
        }
        else if (_input[start] ==',')
        {
            fisrt = true;
            json_state ++;
        }
        else if (_input[start] ==';')
        {
            jsonInfo[i]["valueNum"] = json_state + 1;
            i++;
            json_state = 0;
            fisrt = true;
        }
        start++;
    }
    if (strlen(_input)==0)
    {
        jsonInfo[unsigned(0)]["infoNum"] = 0;
    }
    else
    {
        jsonInfo[unsigned(0)]["infoNum"] = i;
    }
    return jsonInfo;
}



CCSpriteFrame * tinyxmlHellp::gainSpriteFrameByImg(const char * _img)
{
    CCSprite *showSp = new  CCSprite();
    showSp->initWithFile(_img);
    CCSpriteFrame *showFrame = CCSpriteFrame::createWithTexture(showSp->getTexture(), CCRect(showSp->getTextureRect().origin.x, showSp->getTextureRect().origin.y, showSp->getTextureRect().size.width, showSp->getTextureRect().size.height));
    showSp->release();
    showFrame->release();
    return showFrame;
}
const char * tinyxmlHellp::gainValueByElementName(TiXmlElement *Element,const char * ElementName)
{
    TiXmlElement *childElement = tinyxmlHellp::gainElementBychild(Element, ElementName);
    return childElement->GetText();
    
//    childElement->Row()
}

//bool tinyxmlHellp::isTouchOnSprite(CCNode * sprite,CCTouch *pTouch)
//{
//    const CCSize& s = sprite->getContentSize();
//    CCPoint  p = sprite->getAnchorPointInPoints();
//    CCRect r = CCRectMake(-p.x, -p.y, s.width, s.height);
//    CCRect q = CCRectMake(sprite->convertTouchToNodeSpaceAR(pTouch).x,
//                          sprite->convertTouchToNodeSpaceAR(pTouch).y, 1, 1);
    
    //显示log 如果点击正确；
//    if (SpriteByCollide::isRectCollide(r, q))
//    {
//        return true;
//    }
//    return false;
//}
