//
//  HXmlParse.cpp
//  HAnimation
//
//  Created by Himi on 12-3-22.
//  Copyright (c) 2012年 Augustimpression. All rights reserved.
//

#include "HXmlParse.h"
#include "platform/CCSAXParser.h"
#include <string.h>

using namespace std;

HXmlParse * HXmlParse::parserWithFile(const char *tmxFile)
{
    HXmlParse *pRet = new HXmlParse();
    if(pRet->initHXmlParse(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool HXmlParse::initHXmlParse(const char* xmlName)
{
    
    mDic = new CCDictionary();
    
    CCSAXParser _par;
    
    if (false == _par.init("UTF-8") )
        
    {
        CCLog("-----请使用utf-8格式!");
        return false;
    }
    
    _par.setDelegator(this);
    
    const char* _path;
    _path = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlName).c_str();
    
    return _par.parse(_path);
}

//回调函数
void HXmlParse::startElement(void *ctx, const char *name, const char **atts)
{
    
    CC_UNUSED_PARAM(ctx);
    
    startXmlElement = (char*)name;
    if(!isJumpHeadData){//跳过数据头
        CCLog("------跳过root name");
        isJumpHeadData=true;
        root_name=startXmlElement;
        return;
    }
    
    //    CCLog("-startElement----%s",startXmlElement.c_str());
    
}

void HXmlParse::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    
    endXmlElement = (char*)name;
    if(endXmlElement==root_name){//数据尾
        CCLog("读取xml结束");
        isJumpHeadData=false;
        root_name="";
        return;
    }
    
    //    CCLog("-endElement----%s",endXmlElement.c_str());
}
//键值对的结束字段
void HXmlParse::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    currString=string((char*)ch,0,len);
    CCString *ccStr =new CCString();//备注3
    ccStr->m_sString=currString;
    if(root_name!=""){
        mDic->setObject(ccStr,startXmlElement);
        CCLog("-----key:%s, value:%s",startXmlElement.c_str(),dynamic_cast<CCString*>(mDic->objectForKey(startXmlElement))->getCString());
    }
    
    //    CCLog("-textHandler----%s",currString.c_str());
}