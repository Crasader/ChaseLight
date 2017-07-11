//
//  FloatStarObject.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/23.
//
//

#ifndef FloatStarObject_hpp
#define FloatStarObject_hpp

#include "CCBase.h"
#include "ObjectPool.hpp"

class FloatStarObject : public Sprite {
public:
    bool init() override;
    CREATE_FUNC(FloatStarObject);
    void random();
};

#endif /* FloatStarObject_hpp */
