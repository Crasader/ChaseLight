//
//  PlanetStar.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#include "PlanetStar.hpp"

PlanetStar::PlanetStar() {
    _texurefile = "star_moon.png";
    _maxEnergy = 356.f;   //行星最大能量，超过会形成超星星，进而爆炸
    _maxScale  = 2.5f;  //行星最大缩放系数
    _minScale  = .75f;   //行星最小缩放系数
    _maxMoveRadius = 50.f; //行星最大活动半径
    _secEnergy = 1.f * _director->getAnimationInterval();   //行星每秒减能量
    _starType = StarType::PlanetStar;
    setName("PlanetStar");
}

PlanetStar::~PlanetStar() {
    
}

bool PlanetStar::init() {
    if(!BaseStar::init()) {
        return false;
    }
    
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
    body->setContactTestBitmask(CollisionBit::PlanetStar);
    body->setCollisionBitmask(CollisionBit::PlanetStar);
    body->setCategoryBitmask(0xFFFFFFFF);
    body->setMass(StarMass::PlanetStar);
    setTag(CollisionTag::PlanetStar);
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

void PlanetStar::update(float dt) {
    if(_pause)
        return;
    BaseStar::update(dt);
}

void PlanetStar::behaviour(StarEnergyState state) {
    setScale(_minScale+(_energy/_maxEnergy));
    
    if(state == StarEnergyState::Low) {
        //低能量
        stop();
        removeFromParent();
    } else if(state == StarEnergyState::Full) {
        //超星星爆炸💥 TODO
        bigBoom();
    }
}

void PlanetStar::bigBoom() {
    stop();
    auto sca = ScaleBy::create(.5f, 1.1f);
    auto clf = CallFunc::create([=](){
        if(this->getScale() >= _maxScale*1.5f) {
            this->stopAllActions();
            this->setVisible(false);
            this->runAction(Sequence::create(DelayTime::create(2.f), RemoveSelf::create(), NULL));
        }
    });
    auto seq = Sequence::create(sca, clf, NULL);
    runAction(RepeatForever::create(seq));
}

void PlanetStar::collisionMainStar(BaseStar* star) {
    //与主星相撞
    CCLOG("[PlanetStar] collisionMainStar");
    explision(this, star);
    gainEnergy(star->getMaxEnergy()*.02f);
}

void PlanetStar::collisionPlanetStar(BaseStar* star)  {
    //与行星相撞
    CCLOG("[PlanetStar] collisionPlanetStar");
    explision(this, star);
    gainEnergy(star->getEnergy());
}

void PlanetStar::collisionRoundStar(BaseStar* star)  {
    CCLOG("[PlanetStar] collisionPlanetStar");
    explision(this, star);
    gainEnergy(star->getEnergy());
}

void PlanetStar::collisionCosmicDust(BaseStar* star)  {
    CCLOG("[PlanetStar] collisionCosmicDust");
    auto v = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(v*.95f);
}

void PlanetStar::collisionSquareStar(BaseStar* star)  {
    CCLOG("[PlanetStar] collisionSquareStar");
    explision(this, star);
    gainEnergy(-star->getEnergy());
}

void PlanetStar::collisionStellarStar(BaseStar* star) {
    CCLOG("[PlanetStar] collisionStellarStar");
}

void PlanetStar::collisionDipperStar(BaseStar* star)  {
    CCLOG("[PlanetStar] collisionDipperStar");
    auto v = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(-v*.5f);
    gainEnergy(-star->getMaxEnergy() * .1f);
}

void PlanetStar::collisionMeteorStar(BaseStar* star) {
    CCLOG("[PlanetStar] collisionMeteorStar");
    explision(this, star);
    gainEnergy(star->getEnergy()-_maxEnergy*.02f);
}
