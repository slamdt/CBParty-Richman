//
//  RichManMapNode.hpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/3/31.
//
//

#ifndef RichManMapNode_hpp
#define RichManMapNode_hpp

#include "GameUtil.h"

enum NODETYPE {
    BLOCK_EMPTY = 0,
    BLOCK_RANDOM,
    BLOCK_SHOP,
    BLOCK_HOLDED
};

class RichManMapNode : public CCNode {
public:
    CREATE_FUNC(RichManMapNode)
    virtual bool init();
    void initWithDatas(int step, int nodeType);
    void triggerEvent();
private:
    int curStep;
};

#endif /* RichManMapNode_hpp */