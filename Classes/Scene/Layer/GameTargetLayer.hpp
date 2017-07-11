//
//  GameTargetLayer.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef GameTargetLayer_hpp
#define GameTargetLayer_hpp

#include "CCBase.h"
#include "TwinkleTextNode.hpp"

class GameTargetLayer : public Layer {
public:
    bool init() override;
    CREATE_FUNC(GameTargetLayer);
    void onEnter() override;
    void onExit() override;
    
private:
    EventListenerTouchOneByOne* _listener = nullptr;
    TwinkleTextNode* _labTwinkle = nullptr;
};

#endif /* GameTargetLayer_hpp */
