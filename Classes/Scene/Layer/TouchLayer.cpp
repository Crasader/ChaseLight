//
//  TouchLayer.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/20.
//
//

#include "TouchLayer.hpp"
#include "RandomGeometryCom.hpp"

#define TOUCH_ACTION_CONTINUES (1.f)

bool TouchLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    return true;
}

void TouchLayer::onEnter() {
    Layer::onEnter();
    
    _touchCount = 0;

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch *touch, Event *event) {
        return true;
    };
    listener->onTouchEnded = [=](Touch *touch, Event *event) {
        performTouchAction(touch->getLocation());
    };
    _listener = listener;
    _listener->setSwallowTouches(false);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TouchLayer::onExit() {
    _eventDispatcher->removeEventListener(_listener);
    removeAllChildren();
    Layer::onExit();
}

void TouchLayer::generateStar(Vec2 from, Vec2 by) {
    ++_touchCount;
    auto star = Sprite::create("star_square.png");
    star->setScale(.5f);
    star->setPosition(from);
    star->setColor(RandomGeometryCom::randomColor3B());
    auto rot = RotateBy::create(TOUCH_ACTION_CONTINUES, RandomHelper::random_int(0, 180));
    auto mov = MoveBy::create(TOUCH_ACTION_CONTINUES, by);
    auto fad = FadeOut::create(TOUCH_ACTION_CONTINUES);
    auto spw = Spawn::create(mov, fad, rot, NULL);
    auto rev = RemoveSelf::create();
    auto clf = CallFunc::create([this](){
        --_touchCount;
    });
    auto action = Sequence::create(spw, rev, clf, NULL);
    star->runAction(action);
    addChild(star);
}


void TouchLayer::performTouchAction(Vec2 pos) {
    if(_touchCount >= 18) return;
    
    auto r = RandomHelper::random_int(20, 30);
    auto q = sqrt(2);
    generateStar(pos, Vec2(0, -r));
    generateStar(pos, Vec2(0, r));
    generateStar(pos, Vec2(-r, 0));
    generateStar(pos, Vec2(-r, r/q));
    generateStar(pos, Vec2(r,  r/q));
    generateStar(pos, Vec2(r,  0));
    generateStar(pos, Vec2(r,  -r/q));
    generateStar(pos, Vec2(-r, -r/q));
}
