//
//  HeroObject.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "HeroObject.hpp"

bool HeroObject::init() {
    if(!Node::init()) {
        return false;
    }
    
    initWithFile("star_round_2x.png");
    _isPaused = true;
    auto scale = 2.f;
    setColor(Color3B::GOLD);
    addComponent(PhysicsBody::createCircle(getContentSize().width/2, PhysicsMaterial(1.f, 0, 0.0f)));
    getPhysicsBody()->setMass(StarMass::MainStar);
    getPhysicsBody()->setRotationEnable(true);
    getPhysicsBody()->setGravityEnable(false);
    getPhysicsBody()->setLinearDamping(.0f);
    getPhysicsBody()->setAngularDamping(.01f);
    getPhysicsBody()->setContactTestBitmask(CollisionBit::MainStar);
    getPhysicsBody()->setCollisionBitmask(CollisionBit::MainStar);
    getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
    setTag(CollisionTag::MainStar);
    setScale(scale);
    
    return true;
}

void HeroObject::update(float delta) {
    if(_isPaused) return;
    auto p = getPosition();
    p += _speed;
    setPosition(p);
}

void HeroObject::play() {
    if(!_isPaused) return;
    _isPaused = false;
}

void HeroObject::stop() {
    if(_isPaused) return;
    _isPaused = true;
}

void HeroObject::onExit() {
    stop();
    Node::onExit();
}



