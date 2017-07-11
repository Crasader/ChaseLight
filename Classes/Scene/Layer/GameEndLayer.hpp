//
//  GameEndLayer.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef GameEndLayer_hpp
#define GameEndLayer_hpp

#include "CCBase.h"
#include "TwinkleTextNode.hpp"

class GameEndLayer : public Layer {
public:
    CREATE_FUNC(GameEndLayer);
    bool init() override;
    void open();
    void onEnter() override;
    void onExit() override;
    
private:
    Label* _labTarget = nullptr;
    TwinkleTextNode* _labTwinkle = nullptr;
    EventListenerTouchOneByOne* _listener = nullptr;
};

#endif /* GameEndLayer_hpp */
