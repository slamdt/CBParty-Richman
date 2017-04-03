//
//  RichManLayer.hpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/3/18.
//
//

#ifndef RichManLayer_hpp
#define RichManLayer_hpp

#include "BaseLayer.h"
class RichManLayer : public BaseLayer {
public:
    CREATE_FUNC(RichManLayer)
    virtual bool init();
    void drawMap();
    void backToModel();
private:
};

#endif /* RichManLayer_hpp */
