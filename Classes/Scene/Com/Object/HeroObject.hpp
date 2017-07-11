//
//  HeroObject.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef HeroObject_hpp
#define HeroObject_hpp

#include "CCBase.h"
#define MAX_VELOCITY (5.f)

class HeroObject : public Sprite {
public:
    CREATE_FUNC(HeroObject);
    bool init() override;
    void onExit() override;
    void update(float delta) override;
    
    inline void setSpeed(Vec2 speed) {
        if(_speed.x > 0.f)
            _speed.x = MIN(_speed.x, MAX_VELOCITY);
        if(_speed.y > 0.f)
            _speed.y = MIN(_speed.y, MAX_VELOCITY);
        if(_speed.x < 0.f)
            _speed.x = -MIN(-_speed.x, MAX_VELOCITY);
        if(_speed.y < 0.f)
            _speed.y = -MIN(-_speed.y, MAX_VELOCITY);
        _speed = speed;
        CCLOG("speed : %.0f, %.0f", _speed.x, _speed.y);
    }
    inline Vec2 getSpeed() {
        return _speed;
    }
    
    void play();
    void stop();
    
private:
    Vec2 _speed;
    bool _isPaused;
};

#endif /* HeroObject_hpp */
