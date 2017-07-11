//
//  DipperObject.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#include "DipperObject.hpp"
#define STEP    (50.f)

bool DipperObject::init() {
    if(!Node::init()) {
        return false;
    }
    
    auto chapterId = g_User->getCurPlayChapter();
    auto chapterInfo = g_Service->getChapterInfo(chapterId);
    initWithFile(StringUtils::format("star_b%d.png", chapterId));
    setPosition(chapterInfo->coord.x * 10, chapterInfo->coord.y * 10);
    
    addComponent(PhysicsBody::createCircle(getContentSize().width/2, PhysicsMaterial(1.f, 0, 0.0f)));
    getPhysicsBody()->setMass(StarMass::DipperStar);
    getPhysicsBody()->setRotationEnable(true);
    getPhysicsBody()->setGravityEnable(false);
    getPhysicsBody()->setLinearDamping(.0f);
    getPhysicsBody()->setAngularDamping(.0f);
    getPhysicsBody()->setContactTestBitmask(CollisionBit::DipperStar);
    getPhysicsBody()->setCollisionBitmask(CollisionBit::DipperStar);
    getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
    setTag(CollisionTag::DipperStar);
    
    return true;
}

void DipperObject::update(float dt) {
    static float elapsed = 0.f;
    static int movetimes = 0;
    elapsed += dt;
    
    if(elapsed > STEP) {
        elapsed = 0.f;
        stopAllActions();
        auto pos = convertToWorldSpace(getPosition());
        auto vx = RandomHelper::random_real(0.f, SCREEN_WIDTH);
        auto vy = RandomHelper::random_real(0.f, SCREEN_HEIGHT);
        auto rod = RandomHelper::random_int(0, 360);
        auto end = Vec2(vx, vy)+pos;
        auto dst = pos.distance(end);
        auto rot = RotateBy::create(dst, rod);
        auto mov = MoveTo::create(dst, end+pos);
        auto spw = Spawn::create(mov, rot, NULL);
        runAction(spw);
        
        CCLOG("Dipper Moves %d times.", ++movetimes);
    }
}
