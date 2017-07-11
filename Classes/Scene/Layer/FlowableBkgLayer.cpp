//
//  FlowableBkgLayer.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#include "FlowableBkgLayer.hpp"
#include "RandomGeometryCom.hpp"
#define RANDOM_GEOMETRY_SELECTOR_KEY "RandomGeometry"
#define RANDOM_BACKGROUND_SELECTOR_KEY "RandomBackground"

bool FlowableBkgLayer::init() {
    if(!LayerGradient::init()) {
        return false;
    }
    
    setBackgroundColor(Color4F(Color3B(27, 27, 27), 0.f));
    
    _geometryCom = RandomGeometryCom::getInstance();
    
    return true;
}

void FlowableBkgLayer::onEnter() {
    LayerGradient::onEnter();
    
    if(_director->isPaused()) {
        _director->resume();
    }
}

void FlowableBkgLayer::flow() {
    schedule([=](float dt) {
        auto draw2 = DrawNode::create();
        Vec2 v0 = Vec2::ZERO, v1, v2;
        int length = RandomHelper::random_int(20.f, 40.f);
        int height = RandomHelper::random_int(length/2, length);
        v1 = Vec2(0, length);
        v2 = Vec2(height, 0);
        draw2->drawTriangle(v0, v1, v2, _geometryCom->randomColor4F());
        addChild(draw2, 2);
        _geometryCom->randomAction(draw2);
    }, 1.f, RANDOM_GEOMETRY_SELECTOR_KEY);
}

void FlowableBkgLayer::randomBackgroundColor() {
    auto start = _geometryCom->randomColor4F();
    setBackgroundColor(start);
}

void FlowableBkgLayer::setBackgroundColor(Color4F start) {
    auto half1 = RandomHelper::random_real(0.f, 1.f);
    auto half2 = RandomHelper::random_real(0.f, 1.f);
    initWithColor(Color4B(start), Color4B(start), Vec2(half1, half2));
}

void FlowableBkgLayer::onExit() {
    unschedule(RANDOM_GEOMETRY_SELECTOR_KEY);
    LayerColor::onExit();
}
