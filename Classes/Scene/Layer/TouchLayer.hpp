//
//  TouchLayer.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/20.
//
//

#ifndef TouchLayer_hpp
#define TouchLayer_hpp

#include <CCBase.h>

class TouchLayer : public Layer {
public:
    CREATE_FUNC(TouchLayer);
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
private:
    NodeGrid* _grid = nullptr;
    int _touchCount = 0;
    EventListenerTouchOneByOne* _listener = nullptr;
    
    void generateStar(Vec2 from, Vec2 by);
    void performTouchAction(Vec2 pos);
};

#endif /* TouchLayer_hpp */
