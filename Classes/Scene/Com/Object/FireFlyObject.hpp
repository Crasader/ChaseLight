//
//  FireFlyObject.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/25.
//
//

#ifndef FireFlyObject_hpp
#define FireFlyObject_hpp

#include "CCBase.h"

class FireFlyObject : public Sprite {
public:
    CREATE_FUNC(FireFlyObject);
    bool init() override;
    void fly();
};

#endif /* FireFlyObject_hpp */
