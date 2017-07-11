//
//  FireFlyObject.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/25.
//
//

#include "FireFlyObject.hpp"
#define MARGIN (50.f)

bool FireFlyObject::init() {
    if(!Sprite::init()) {
        return false;
    }
    
    initWithFile("firefly.png");
    auto vx = RandomHelper::random_real(-MARGIN, SCREEN_WIDTH+MARGIN);
    auto vy = RandomHelper::random_real(-MARGIN, SCREEN_HEIGHT+MARGIN);
    setPosition(vx, vy);
    
    return true;
}

void FireFlyObject::fly() {
    stopAllActions();
    setColor(RandomGeometryCom::randomColor3B());
    auto pos = getPosition();
    auto vx = RandomHelper::random_real(-MARGIN, SCREEN_WIDTH+MARGIN);
    auto vy = RandomHelper::random_real(-MARGIN, SCREEN_HEIGHT+MARGIN);
    auto op = RandomHelper::random_int(50, 100);
    auto fd = RandomHelper::random_real(0.5f, 2.5f);
    auto fad = FadeTo::create(fd, op);
    auto fau = FadeTo::create(fd, 255);
    auto dlt = DelayTime::create(.5f);
    auto end = Vec2(vx, vy);
    auto dst = pos.distance(end);
    auto mvt = dst / 15.f;
    auto rot = RotateBy::create(mvt, 10);
    auto fsq = Sequence::create(fad, dlt, fau, NULL);
    auto rep = Repeat::create(fsq, mvt / (fd*2+.5f));
    auto mov = MoveTo::create(mvt, end);
    auto spw = Spawn::create(rep, mov, rot, NULL);
    auto ldt = DelayTime::create(2.f);
    auto clf = CallFunc::create([this]() {
        fly();
    });
    auto seq = Sequence::create(spw, ldt, clf, NULL);
    runAction(RepeatForever::create(seq));
}
