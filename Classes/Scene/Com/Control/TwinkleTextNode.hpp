//
//  TwinkleTextNode.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef TwinkleTextNode_hpp
#define TwinkleTextNode_hpp

#include "CCBase.h"

class TwinkleTextNode : public Label {
public:
    CREATE_FUNC(TwinkleTextNode);
    bool init() override;
    
    void fade();
    void onEnter() override;
    void onExit() override;
};

#endif /* TwinkleTextNode_hpp */
