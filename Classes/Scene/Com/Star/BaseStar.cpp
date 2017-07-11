//
//  BaseStar.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#include "BaseStar.hpp"

BaseStar::BaseStar() {
    _texurefile= "";  //精灵纹理
    _energy    = 0.f; //当前能量
    _maxEnergy = 0.f; //最大能量
    _secEnergy = 1.f * _director->getAnimationInterval(); //每秒减能量
    _moveScope = Vec2::ZERO; //运动范围
    _starType = StarType::None;
}

BaseStar::~BaseStar() {
    removeComponent(COMPONENT_PHYSICS_BODY);
    StarFactory::getInstance()->decrease(_starType);
}

bool BaseStar::init() {
    if(!Sprite::init()) {
        return false;
    }
    
    if(!StarFactory::getInstance()->increase(_starType)) {
        return false;
    }
    
    return true;
}

void BaseStar::bindMotionStreak() {
    if(_streak && getParent()) return;
    
    auto streak = MotionStreak::create(1.f, -1.0f, 2.f, getColor(), "streak.png");
    streak->setOpacity(80);
    streak->setFastMode(false);
    streak->setName("StarStreak");
    streak->setTarget(this);
    streak->setVisible(false);
    getParent()->addChild(streak, ZOrder::StarStreak);
    
    auto off = getContentSize().width * .3f;
    auto rb1 = MoveBy::create(.35f, Vec2(off,off));
    auto rb2 = MoveBy::create(.35f, Vec2(-off,-off));
    auto dlt = DelayTime::create(.5f);
    auto fd1 = FadeTo::create(3.f, 60);
    auto fd2 = FadeTo::create(7.f, 100);
    auto seq = Sequence::create(rb1, fd1, dlt, rb2, dlt, rb1->reverse(), rb2->reverse(), fd2, NULL);
    streak->runAction(RepeatForever::create(seq));
    
    _streak = streak;
}

void BaseStar::behaviour() {
    if(isLow()) {
        behaviour(StarEnergyState::Low);
    } else if(isFull()) {
        behaviour(StarEnergyState::Full);
    } else {
        behaviour(StarEnergyState::Normal);
    }
}

void BaseStar::behaviour(StarEnergyState state) {}

bool BaseStar::isLow() {
    return NAGATIVEF(_energy);
}

bool BaseStar::isFull() {
    return _energy >= _maxEnergy;
}

bool BaseStar::gainEnergy(float energy) {
    bool isOK = false;
    
    energy += _energy;
    if(energy >= _maxEnergy) {
        _energy = _maxEnergy+_secEnergy;
        isOK = false;
    } else if(NAGATIVEF(energy)) {
        _energy = -1.f; //用一个负数标识它可以被回收了
        isOK = false;
    } else {
        _energy = energy;
        isOK = true;
    }
    
    updateScale();
    
    return isOK;
}

void BaseStar::updateScale() {
    if(_starType == StarType::MainStar)
        return;
    
    auto scale = _energy / _maxEnergy * _maxScale;
    scale = MAX(scale, _minScale); //不可能为0
    setScale(scale);
}

void BaseStar::update(float dt) {
    if(_pause) return;
    
    //streak 移动
    checkStreak(dt);
    
    //减能量
    gainEnergy(-_secEnergy);
    
    //行为应该放在最后做，因为行为中可能有移除操作
    behaviour();
}

void BaseStar::checkStreak(float dt) {
    if(_streak) {
        _streak->update(dt);
    }
}

void BaseStar::start() {
    
//    schedule([=](float dt) {
//        gainEnergy(-_secEnergy);
//    }, 1.f, SchedulerCode::MainStarEnergyDecrease);
//    unschedule(SchedulerCode::MainStarEnergyDecrease);
    
    if(!_pause) return;
    
    _pause = false;
    
//    scheduleUpdate();
}

void BaseStar::stop() {
    if(_pause) return;
    
    _pause = true;
    unscheduleUpdate();
    
    if(_streak && _streak->getReferenceCount() > 0)
        _streak->detachTarget();
}

void BaseStar::onEnter() {
    Sprite::onEnter();
}

void BaseStar::onExit() {
    stop();
    
    Sprite::onExit();
}

void BaseStar::collision(BaseStar* star) {
    StarType type = star->getStarType();
    switch (type) {
        case StarType::MainStar: {
            collisionMainStar(star);
        }
            break;
            
        case StarType::RoundStar:
        {
            collisionRoundStar(star);
        }
            break;
            
        case StarType::SquareStar:
        {
            collisionSquareStar(star);
        }
            break;
            
        case StarType::CosmicDust:
        {
            collisionCosmicDust(star);
        }
            break;
            
        case StarType::PlanetStar:
        {
            collisionPlanetStar(star);
        }
            break;
            
        case StarType::StellarStar:
        {
            collisionStellarStar(star);
        }
            break;
        
        case StarType::DipperStar:
        {
            collisionDipperStar(star);
        }
            break;
            
        case StarType::MeteorStar:
        {
            collisionMeteorStar(star);
        }
            break;
            
        case StarType::None:
        default:
            break;
    }
}

void BaseStar::collisionMainStar(BaseStar* star) {
    CCLOG("[BaseStar] collisionMainStar");
}

void BaseStar::collisionRoundStar(BaseStar* star)  {
    CCLOG("[BaseStar] collisionRoundStar");
}

void BaseStar::collisionSquareStar(BaseStar* star)  {
    CCLOG("[BaseStar] collisionSquareStar");
}

void BaseStar::collisionCosmicDust(BaseStar* star)  {
    CCLOG("[BaseStar] collisionCosmicDust");
}

void BaseStar::collisionPlanetStar(BaseStar* star)  {
    CCLOG("[BaseStar] collisionPlanetStar");
}

void BaseStar::collisionStellarStar(BaseStar* star) {
    CCLOG("[BaseStar] collisionStellarStar");
}

void BaseStar::collisionDipperStar(BaseStar* star)  {
    CCLOG("[BaseStar] collisionDipperStar");
}

void BaseStar::collisionMeteorStar(BaseStar* star) {
    CCLOG("[BaseStar] collisionMeteorStar");
}

