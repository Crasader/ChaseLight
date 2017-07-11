//
//  JoyStickLayer.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef JoyStickLayer_hpp
#define JoyStickLayer_hpp

#include "CCBase.h"
#include "MainStar.hpp"

class JoyStickLayer final : public Layout {
private:
    JoyStickLayer();
    static JoyStickLayer* _instance;
public:
    static JoyStickLayer* getInstance() {
        if(!_instance) {
            _instance = JoyStickLayer::create();
        }
        return _instance;
    }
    
    CREATE_FUNC(JoyStickLayer);
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
    void bindMainStar(MainStar* star){
        if(!star) return;
        _mainStar = star;
    }
    
    bool onTouchBegan(Touch* touch, Event* event) override;
    void onTouchMoved(Touch* touch, Event* event) override;
    void onTouchEnded(Touch* touch, Event* event) override;
    void onTouchCancelled(Touch* touch, Event* event) override;

protected:
    Vec2 _touchPrev;
    MainStar* _mainStar = nullptr;
    Node* _drawCircle = nullptr;
    Node* _drawBall = nullptr;
    
};

#endif /* JoyStickLayer_hpp */
