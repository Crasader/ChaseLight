//
//  RoundStar.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#include "RoundStar.hpp"

RoundStar::RoundStar() {
    _texurefile = "star_round_2x.png";
    _maxEnergy = 25.f;  //圆星最大能量，超过会形成超星星，进而爆炸
    _maxScale  = 2.5f;  //圆星最大缩放系数
    _minScale  = 1.0f;   //圆星最小缩放系数
    _maxMoveRadius = 100.f; //圆星最大活动半径
    _secEnergy = 1.f * _director->getAnimationInterval();   //圆星每秒减能量
    _starType = StarType::RoundStar;
    setName("RoundStar");
}

RoundStar::~RoundStar() {
    
}


bool RoundStar::init() {
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
    body->setContactTestBitmask(CollisionBit::RoundStar);
    body->setCollisionBitmask(CollisionBit::RoundStar);
    body->setCategoryBitmask(0xFFFFFFFF);
    body->setMass(StarMass::RoundStar);
    setTag(CollisionTag::RoundStar);
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

void RoundStar::update(float dt) {
    if(_pause)
        return;
    BaseStar::update(dt);
}

void RoundStar::behaviour(StarEnergyState state) {
    if(state == StarEnergyState::Low) {
        //低能量，消失
        stop();
        removeFromParent();
        CCLOG("RoundStar低能量移除");
    }
}

void RoundStar::collisionMainStar(BaseStar* star) {
    CCLOG("[RoundStar] collisionMainStar");
    explision(this, star);
    if(_energy > .8f*_maxEnergy) {
        gainEnergy(-_maxEnergy * .20f);
    } else if(_energy > .5f*_maxEnergy) {
        gainEnergy(-_maxEnergy * .15f);
    } else {
        gainEnergy(-_maxEnergy * .10f);
    }
}

void RoundStar::collisionRoundStar(BaseStar* star)  {
    //两个圆星相撞，高能量的圆星从低能量圆星获得能量差值
    CCLOG("[RoundStar] collisionRoundStar");
    if(getScale() > star->getScale())
        explision(this, star);
    gainEnergy(_energy - star->getEnergy());
}

void RoundStar::collisionSquareStar(BaseStar* star)  {
    CCLOG("[RoundStar] collisionSquareStar");
    gainEnergy(-_maxEnergy * .1f);
}

void RoundStar::collisionCosmicDust(BaseStar* star)  {
    CCLOG("[RoundStar] collisionCosmicDust");
    auto v = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(v*.95f);
}

void RoundStar::collisionPlanetStar(BaseStar* star)  {
    CCLOG("[RoundStar] collisionPlanetStar");
    explision(this, star);
    gainEnergy(-_energy);
}

void RoundStar::collisionStellarStar(BaseStar* star) {
    CCLOG("[RoundStar] collisionStellarStar");
    explision(this, star);
    gainEnergy(-_energy);
}

void RoundStar::collisionDipperStar(BaseStar* star)  {
    CCLOG("[RoundStar] collisionDipperStar");
    explision(this, star);
    gainEnergy(-_energy);
}

void RoundStar::collisionMeteorStar(BaseStar* star) {
    CCLOG("[RoundStar] collisionMeteorStar");
    gainEnergy(_maxEnergy * .1f);
}
