//
//  DipperObject.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef DipperObject_hpp
#define DipperObject_hpp

#include "CCBase.h"

class DipperObject : public Sprite {
public:
    CREATE_FUNC(DipperObject);
    bool init() override;
    void update(float delta) override;
};

#endif /* DipperObject_hpp */
