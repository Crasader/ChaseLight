//
//  DipperStar.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#include "DipperStar.hpp"

DipperStar::DipperStar() {
    _texurefile = "star_b1.png";
    _maxEnergy = 100.f;     //北斗星最大能量
    _maxScale  = 1.0f;      //北斗星最大缩放系数
    _minScale  = 1.0f;      //北斗星最小缩放系数
    _maxMoveRadius = 10.f;  //北斗星最大活动半径
    _secEnergy = .000001f * _director->getAnimationInterval();   //北斗星每秒减能量
    _starType = StarType::DipperStar;
    setName("DipperStar");
}

DipperStar::~DipperStar() {
    
}

bool DipperStar::init() {
    if(!BaseStar::init()) {
        return false;
    }
    
    auto chapterId = g_User->getCurPlayChapter();
    _texurefile = StringUtils::format("star_b%d.png", chapterId);
    initWithFile(_texurefile);
    
    //物理形体
    auto radius = getContentSize().width * .45f;
    auto body = PhysicsBody::createCircle(radius, PhysicsMaterial(1.0f, 1.f, 1.0f));
    body->setName(COMPONENT_PHYSICS_BODY);
    body->setRotationEnable(false);
    body->setGravityEnable(false);
    body->setDynamic(true);
    body->setLinearDamping(1.f);
    body->setAngularDamping(1.f);
    body->setContactTestBitmask(CollisionBit::DipperStar);
    body->setCollisionBitmask(CollisionBit::DipperStar);
    body->setCategoryBitmask(0xFFFFFFFF);
    body->setMass(StarMass::DipperStar);
    setTag(CollisionTag::DipperStar);
    addComponent(body);
    
    //初始位置
    auto chapterInfo = g_Service->getChapterInfo(chapterId);
    setPosition(chapterInfo->coord.x * 10, chapterInfo->coord.y * 10);
    
    //初始能量
    gainEnergy(_maxEnergy);
    
    //活动范围
    float off_x = RandomHelper::random_real(-_maxMoveRadius, _maxMoveRadius);
    float off_y = RandomHelper::random_real(-_maxMoveRadius, _maxMoveRadius);
    _moveScope = Vec2(off_x, off_y);
    body->setVelocity(_moveScope);
    
    //是否停止更新运行状态
    _pause = false;
    
    return true;
}

void DipperStar::update(float dt) {
    if(_pause)
        return;
    BaseStar::update(dt);
}

void DipperStar::behaviour(StarEnergyState state) {
    if(state == StarEnergyState::Low) {
        
    } else if(state == StarEnergyState::Full) {

    } else if(state == StarEnergyState::Normal) {
        
    }
}

void DipperStar::collisionMainStar(BaseStar* star) {
    CCLOG("[DipperStar] collisionMainStar");
}

void DipperStar::collisionRoundStar(BaseStar* star)  {
    CCLOG("[DipperStar] collisionRoundStar");
    gainEnergy(star->getEnergy());
}

void DipperStar::collisionSquareStar(BaseStar* star)  {
    CCLOG("[DipperStar] collisionSquareStar");
    gainEnergy(star->getEnergy());
}

void DipperStar::collisionCosmicDust(BaseStar* star)  {
    CCLOG("[DipperStar] collisionCosmicDust");
    auto v = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(v*.95f);
}

void DipperStar::collisionPlanetStar(BaseStar* star)  {
    CCLOG("[DipperStar] collisionPlanetStar");
    auto v = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(-v*.5f);
    gainEnergy(-star->getMaxEnergy() * .01f);
}

void DipperStar::collisionStellarStar(BaseStar* star) {
    CCLOG("[DipperStar] collisionStellarStar");
}

void DipperStar::collisionDipperStar(BaseStar* star)  {
    CCLOG("[DipperStar] collisionDipperStar will never happen");
}

void DipperStar::collisionMeteorStar(BaseStar* star) {
    CCLOG("[DipperStar] collisionMeteorStar");
    gainEnergy(star->getEnergy());
}
