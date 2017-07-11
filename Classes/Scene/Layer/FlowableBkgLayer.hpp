//
//  FlowableBkgLayer.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#ifndef GameStartLayer_hpp
#define GameStartLayer_hpp

#include <CCBase.h>
#include "RandomGeometryCom.hpp"

class FlowableBkgLayer final : public LayerGradient {
public:
    CREATE_FUNC(FlowableBkgLayer);
    bool init() override;
    
    void onEnter() override;
    void onExit() override;
    
    void flow();
    void randomBackgroundColor();
    void setBackgroundColor(Color4F start);
    
private:
    RandomGeometryCom* _geometryCom;
    
};

#endif /* GameStartLayer_hpp */
