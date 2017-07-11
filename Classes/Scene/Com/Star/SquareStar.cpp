//
//  SquareStar.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#include "SquareStar.hpp"

SquareStar::SquareStar() {
    _texurefile = "star_square.png";
    _maxEnergy = 35.f;   //方星最大能量，超过会形成超星星，进而爆炸
    _maxScale  = 1.35f;  //方星最大缩放系数
    _minScale  = .75f;   //方星最小缩放系数
    _maxMoveRadius = 50.f; //方星最大活动半径
    _secEnergy = 1.f * _director->getAnimationInterval();   //方星每秒减能量
    _starType = StarType::SquareStar;
    setName("SquareStar");
}

SquareStar::~SquareStar() {
    
}


bool SquareStar::init() {
    if(!BaseStar::init()) {
        return false;
    }
    
    initWithFile(_texurefile);
    
    //物理形体
    auto radius = getContentSize().width * .4f;
    auto body = PhysicsBody::createCircle(radius, PhysicsMaterial(1.0f, 1.f, 1.0f));
    body->setName(COMPONENT_PHYSICS_BODY);
    body->setRotationEnable(false);
    body->setGravityEnable(false);
    body->setDynamic(true);
    body->setLinearDamping(1.f);
    body->setAngularDamping(1.f);
    body->setContactTestBitmask(CollisionBit::SquareStar);
    body->setCollisionBitmask(CollisionBit::SquareStar);
    body->setCategoryBitmask(0xFFFFFFFF);
    body->setMass(StarMass::SquareStar);
    setTag(CollisionTag::SquareStar);
    addComponent(body);
    
    //颜色
    setColor(RandomGeometryCom::randomColor3B());
    
    //缩放（大小）
    auto scale = RandomHelper::random_real(_minScale, _maxScale);
    setScale(scale);
    
    //初始位置
    setPosition(RandomGeometryCom::getInstance()->randomPointOutScreen());
    
    //初始能量
    auto energy_initial = scale / _maxScale * _maxEnergy;
    gainEnergy(energy_initial);
    
    //活动范围
    float off_x = RandomHelper::random_real(-_maxMoveRadius, _maxMoveRadius);
    float off_y = RandomHelper::random_real(-_maxMoveRadius, _maxMoveRadius);
    _moveScope = Vec2(off_x, off_y);
    body->setVelocity(_moveScope);
    
    //是否停止更新运行状态
    _pause = false;
    
    return true;
}

void SquareStar::update(float dt) {
    if(_pause)
        return;
    BaseStar::update(dt);
}

void SquareStar::behaviour(StarEnergyState state) {
    setOpacity(MAX(_energy/_maxEnergy*255, 80));
    
    if(state == StarEnergyState::Low) {
        //低能量，消失
        stop();
        removeFromParent();
        CCLOG("SquareStar低能量移除");
    }
}

void SquareStar::collisionMainStar(BaseStar* star) {
    CCLOG("[SquareStar] collisionMainStar");
    explision(this, star);
    gainEnergy(star->getMaxEnergy() * .05f);
}

void SquareStar::collisionSquareStar(BaseStar* star)  {
    CCLOG("[SquareStar] collisionSquareStar");
    if(getScale() > star->getScale())
        explision(this, star);
    gainEnergy(-star->getEnergy());
}

void SquareStar::collisionRoundStar(BaseStar* star)  {
    CCLOG("[SquareStar] collisionSquareStar");
    explision(this, star);
    gainEnergy(star->getMaxEnergy() * .1f);
}

void SquareStar::collisionCosmicDust(BaseStar* star)  {
    CCLOG("[SquareStar] collisionCosmicDust");
    explision(this, star);
    auto v = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(v*.95f);
}

void SquareStar::collisionPlanetStar(BaseStar* star)  {
    CCLOG("[SquareStar] collisionPlanetStar");
    explision(this, star);
    gainEnergy(-_energy);
}

void SquareStar::collisionStellarStar(BaseStar* star) {
    CCLOG("[SquareStar] collisionStellarStar");
    explision(this, star);
    gainEnergy(-_energy);
}

void SquareStar::collisionDipperStar(BaseStar* star)  {
    CCLOG("[SquareStar] collisionDipperStar");
    explision(this, star);
    gainEnergy(-_energy);
}

void SquareStar::collisionMeteorStar(BaseStar* star) {
    CCLOG("[SquareStar] collisionMeteorStar");
    explision(this, star);
    gainEnergy(-star->getEnergy());
}
