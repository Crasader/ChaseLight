//
//  FloatStarObject.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/23.
//
//

#include "FloatStarObject.hpp"
#include "RandomGeometryCom.hpp"
#include "ObjectPool.hpp"

bool FloatStarObject::init() {
    if(!Sprite::init()) {
        return false;
    }
    
    std::vector<std::string> stars = {
        "star_solid.png",
        "star_square.png",
        "star_round_2x.png",
        "star_moon.png",
    };
    
    auto idx = RandomHelper::random_int(0, (int)stars.size()-1);
    initWithFile(stars[idx]);
    
    auto scale = RandomHelper::random_real(.8f, 1.6f);
    auto size = getContentSize();
    addComponent(PhysicsBody::createCircle(size.width/2, PhysicsMaterial(scale, 0.f, 0.0f)));
    getPhysicsBody()->setMass(StarMass::RoundStar);
    getPhysicsBody()->setRotationEnable(false);
    getPhysicsBody()->setGravityEnable(false);
    getPhysicsBody()->setLinearDamping(.0f);
    getPhysicsBody()->setAngularDamping(.1f);
    getPhysicsBody()->setContactTestBitmask(CollisionBit::RoundStar);
    getPhysicsBody()->setCollisionBitmask(CollisionBit::RoundStar);
    getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
    setTag(CollisionTag::RoundStar);
    
    return true;
}

void FloatStarObject::random() {
    auto randomcom = RandomGeometryCom::getInstance();
    auto size = SCREEN_SIZE;
    auto scale = getScale();
    auto opacity = RandomHelper::random_int(50, 125);
    auto coor = randomcom->randomPointOutScreen();
    auto coorb = randomcom->randomPointOutScreen();
    auto fade = scale * 10;
    auto ac1 = FadeTo::create(fade, opacity*2);
    auto dlt = DelayTime::create(fade);
    auto ac2 = FadeTo::create(fade, opacity);
    auto conf = ccBezierConfig();
    conf.endPosition = coorb;
    conf.controlPoint_1 = (coorb - coor) * sqrt(3) * .3f;
    conf.controlPoint_2 = (coorb - coor) * sqrt(2) * .7f;
    auto bezier = BezierBy::create(fade, conf);
    auto loop = int(scale * 5);
    auto seq = Sequence::create(ac1, dlt, ac2, NULL);
    auto spw = Spawn::create(bezier, seq, NULL);
    auto rep = Sequence::create(Repeat::create(spw, loop), RemoveSelf::create(true), NULL);
    setOpacity(opacity);
    setColor(randomcom->randomColor3B());
    setScale(scale);
    setPosition(coor);
    runAction(rep);

}
