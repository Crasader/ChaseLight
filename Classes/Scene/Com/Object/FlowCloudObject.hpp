//
//  FlowCloudObject.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/24.
//
//

#ifndef FlowCloudObject_hpp
#define FlowCloudObject_hpp

#include "CCBase.h"

class FlowCloudObject : public Sprite {
public:
    CREATE_FUNC(FlowCloudObject);
    bool init() override;
    
    void onEnter() override;
    void onExit() override;
    void update(float dt) override;
};

#endif /* FlowCloudObject_hpp */
