//
//  RichManPopLayer.hpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/4/1.
//
//

#ifndef RichManPopLayer_hpp
#define RichManPopLayer_hpp

#include "BaseLayer.h"

class RichManPopLayer : public BaseLayer {
public:
    CREATE_FUNC(RichManPopLayer)
    virtual bool init();
    void makeContentWithType(int type);
    void countDown();
    void makeForwardBlocks();
    void forwardOver();
    void closeLayer();
private:
    CCLabelTTF* countDonwLabel;
    BoFlash* fowardFlash;
};

#endif /* RichManPopLayer_hpp */
