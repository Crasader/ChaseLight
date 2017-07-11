//
//  MeteorStar.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#include "MeteorStar.hpp"

#define REMAIN (.0f)

MeteorStar::MeteorStar() {
    _texurefile = "star_moon.png";
    _maxEnergy = 10.f;  //流星最大能量
    _maxScale  = .15f;    //流星最大缩放系数
    _minScale  = .15f;    //流星最小缩放系数
    _maxMoveRadius = 166.f; //流星最大活动半径
    _secEnergy = 1.f * _director->getAnimationInterval();//流星每秒减能量
    _starType = StarType::MeteorStar;
    setName("MeteorStar");
}

MeteorStar::~MeteorStar() {
    StarFactory::getInstance()->decrease(_starType);
}

bool MeteorStar::init() {
    if(!BaseStar::init()) {
        return false;
    }
    
    if(!StarFactory::getInstance()->increase(_starType)) {
        return false;
    }
    
    initWithFile(_texurefile);
    
    //颜色
    auto color = RandomGeometryCom::randomColor3B();
    setColor(color);
    
    //物理形体
    auto radius = getContentSize().width * .45f;
    auto body = PhysicsBody::createCircle(radius, PhysicsMaterial(1.0f, 1.f, 1.0f));
    body->setName(COMPONENT_PHYSICS_BODY);
    body->setRotationEnable(false);
    body->setGravityEnable(false);
    body->setDynamic(true);
    body->setLinearDamping(1.f);
    body->setAngularDamping(1.f);
    body->setContactTestBitmask(CollisionBit::MeteorStar);
    body->setCollisionBitmask(CollisionBit::MeteorStar);
    body->setCategoryBitmask(0xFFFFFFFF);
    body->setMass(StarMass::MeteorStar);
    setTag(CollisionTag::MeteorStar);
    addComponent(body);
    
    //缩放（大小）
    auto scale = .2f; //RandomHelper::random_real(_minScale, _maxScale);
    setScale(scale);
    
    //初始位置
    setPosition(RandomGeometryCom::getInstance()->randomPointOutScreen());
    
    //初始能量
    gainEnergy(_maxEnergy);
    
    //活动范围
    float off_x0 = RandomHelper::random_real(-_maxMoveRadius, -_maxMoveRadius*.5f);
    float off_y0 = RandomHelper::random_real(-_maxMoveRadius, -_maxMoveRadius*.5f);
    float off_x1 = RandomHelper::random_real(_maxMoveRadius*.5f, _maxMoveRadius);
    float off_y1 = RandomHelper::random_real(_maxMoveRadius*.5f, _maxMoveRadius);
    _moveScope = RandomHelper::random_real(.0f, 1.f) < .5f ? Vec2(off_x0, off_y0) : Vec2(off_x1, off_y1);
    body->setVelocity(_moveScope);
    
    //是否停止更新运行状态
    _pause = false;
    
    //粒子
    ParticleSystem* ps = ParticleMeteor::create();
    ps->setLifeVar(.1f);
    ps->setStartColor(Color4F(color));
    ps->setEndColor(Color4F(color));
    ps->setEmissionRate(50.f);
    ps->setStartSize(1.f);
    ps->setEndSize(.5f);
    ps->setSpeed(3.f);
    ps->setGravity(-_moveScope);
    ps->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);
    ps->setPosition(Vec2(radius,radius));
    ps->setTexture(Director::getInstance()->getTextureCache()->addImage("star_solid.png"));
    addChild(ps,1,"PS");
    
    auto sprite = Sprite::create(_texurefile);
    sprite->setScale(scale);
    sprite->setPosition(Vec2(radius,radius));
    addChild(sprite,2);
    
    return true;
}

void MeteorStar::update(float dt) {
    if(_pause)
        return;

    BaseStar::update(dt);
}

void MeteorStar::behaviour(StarEnergyState state) {
    
    setOpacity(_energy/_maxEnergy*255);
    auto ps = getChildByName<ParticleSystem*>("PS");
    if(ps) {
        ps->setGravity(-getPhysicsBody()->getVelocity());
        ps->setOpacity(getOpacity());
    }
    
    if(state == StarEnergyState::Low) {
        //低能量，消失
        stop();
        removeFromParent();
        CCLOG("MeteorStar低能量移除");
    }
}

void MeteorStar::collisionMainStar(BaseStar* star) {
    //与主星相撞，爆炸消失
    CCLOG("[MeteorStar] collisionMainStar");
    gainEnergy(-_energy+REMAIN);
}

void MeteorStar::collisionRoundStar(BaseStar* star)  {
    //与圆星相撞，爆炸消失
    CCLOG("[MeteorStar] collisionMeteorStar");
    gainEnergy(-_energy+REMAIN);
}

void MeteorStar::collisionSquareStar(BaseStar* star)  {
    CCLOG("[MeteorStar] collisionSquareStar");
    gainEnergy(-_energy+REMAIN);
}

void MeteorStar::collisionCosmicDust(BaseStar* star)  {
    CCLOG("[MeteorStar] collisionCosmicDust");
    gainEnergy(-_energy+REMAIN);
}

void MeteorStar::collisionPlanetStar(BaseStar* star)  {
    CCLOG("[MeteorStar] collisionPlanetStar");
    gainEnergy(-_energy+REMAIN);
}

void MeteorStar::collisionStellarStar(BaseStar* star) {
    CCLOG("[MeteorStar] collisionStellarStar");
    gainEnergy(-_energy+REMAIN);
}

void MeteorStar::collisionDipperStar(BaseStar* star)  {
    CCLOG("[MeteorStar] collisionDipperStar");
    gainEnergy(-_energy+REMAIN);
}

void MeteorStar::collisionMeteorStar(BaseStar* star) {
    CCLOG("[MeteorStar] collisionMeteorStar");
    gainEnergy(-_energy+REMAIN);
}
