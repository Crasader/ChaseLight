//
//  JoyStickLayer.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "JoyStickLayer.hpp"
#include "MultiTouchHelper.hpp"
#define MARGIN (12)
#define SIDE_LENGTH (50)
#define RADIUS (SIDE_LENGTH * .5f)

JoyStickLayer* JoyStickLayer::_instance = nullptr;

JoyStickLayer::JoyStickLayer() {
    _touchPrev = Vec2::ZERO;
}

bool JoyStickLayer::init() {
    if ( !Layout::init() ) {
        return false;
    }
    
    setContentSize(SCREEN_SIZE);
    
    return true;
}

void JoyStickLayer::onEnter() {
    Layout::onEnter();
    setTouchEnabled(true);
}

void JoyStickLayer::onExit() {
    Layout::onExit();
}

bool JoyStickLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    auto p = touch->getLocation();
    _touchPrev = p;
    return true;
}

void JoyStickLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {

}

void JoyStickLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) {

}

void JoyStickLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    Vec2 p = touch->getLocation();
    float dist = p.distance(_touchPrev);
    if(ZEROF(dist)) return;
    
    float ratio = RADIUS / dist;
    Vec2 t = (p - _touchPrev) * ratio;
    Vec2 a = 250.f * t / RADIUS;
    
    if(_mainStar && _mainStar->getReferenceCount() > 0)
        _mainStar->setMoveScope(a);
}
