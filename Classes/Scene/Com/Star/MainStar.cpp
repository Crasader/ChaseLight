//
//  MainStar.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/27.
//
//

#include "MainStar.hpp"

#ifndef NDEBUG
#define SCALE_SCOPE (1.f)
#else
#define SCALE_SCOPE (2.5f)
#endif

MainStar::MainStar() {
    _score = 0;
    _texurefile = "star_round_2x.png";
    _maxEnergy = 60.f;
    _starType = StarType::MainStar;
    _maxScale  = 2.f;  //主星最大缩放系数
    _minScale  = 2.f;  //主星最小缩放系数
    _secEnergy = 1.f * _director->getAnimationInterval();  //主星每秒减能量
    _maxMoveRadius = 80.f * SCALE_SCOPE; //圆星最大活动半径
    setName("MainStar");
}

MainStar::~MainStar() {

}

bool MainStar::init() {
    if(!BaseStar::init()) {
        return false;
    }
    
    initWithFile(_texurefile);
    _pause = false;
    
    //最大能量值
    auto chapterId = g_User->getCurPlayChapter();
    auto chapterInfo = g_Service->getChapterInfo(chapterId);
    _maxEnergy = MAX(_maxEnergy, chapterInfo->condition_time);
    
    //物理形体
    auto radius = getContentSize().width * .5f;
    auto body = PhysicsBody::createCircle(radius, PhysicsMaterial(1.f, 1.f, .0f));
    body->setName(COMPONENT_PHYSICS_BODY);
    body->setDynamic(true);
    body->setRotationEnable(false);
    body->setGravityEnable(false);
    body->setLinearDamping(.0f);
    body->setAngularDamping(.01f);
    body->setContactTestBitmask(CollisionBit::MainStar);
    body->setCollisionBitmask(CollisionBit::MainStar);
    body->setCategoryBitmask(0xFFFFFFFF);
    body->setMass(StarMass::MainStar);
    setTag(CollisionTag::MainStar);
    addComponent(body);
    unscheduleUpdate();
    
    //颜色
    setColor(Color3B::GOLD);
    
    //缩放（大小）
    setScale(2.f);
    
    //初始位置
    setPosition(SCREEN_CENTER);
    
    //能量
    gainEnergy(_maxEnergy);
    
    //活动范围
    _moveScope = Vec2::ZERO;
    
    //粒子
    ParticleSystem* ps = ParticleMeteor::create();
    ps->setLifeVar(.1f);
    ps->setStartColor(Color4F(Color3B::GOLD));
    ps->setEndColor(Color4F(Color3B::GOLD));
    ps->setEmissionRate(90.f);
    ps->setStartSize(.1f);
    ps->setEndSize(.1f);
    ps->setSpeed(3.f);
    ps->setPosition(Vec2(radius,radius));
    ps->setTexture(Director::getInstance()->getTextureCache()->addImage("streak.png"));
    ps->setScale(.1f);
    addChild(ps,1,"PS");
    
    auto sprite = Sprite::create(_texurefile);
//    sprite->setScale(2.f);
    sprite->setPosition(Vec2(radius,radius));
    sprite->setColor(Color3B::GOLD);
    addChild(sprite,2);
    
    return true;
}

void MainStar::update(float dt) {
    if(_pause) return;
    BaseStar::update(dt);
}

void MainStar::setMoveScope(cocos2d::Vec2 speed) {
    _moveScope = speed * SCALE_SCOPE;
    
    if( POSITIVEF(_moveScope.x) )
        _moveScope.x = MIN(_moveScope.x, _maxMoveRadius);
    
    if( POSITIVEF(_moveScope.y) )
        _moveScope.y = MIN(_moveScope.y, _maxMoveRadius);
    
    if( NAGATIVEF(_moveScope.x) )
        _moveScope.x = -MIN(-_moveScope.x, _maxMoveRadius);
    
    if( NAGATIVEF(_moveScope.y) )
        _moveScope.y = -MIN(-_moveScope.y, _maxMoveRadius);
    
    getPhysicsBody()->setVelocity(_moveScope);
}

void MainStar::behaviour(StarEnergyState state) {
    
    auto ps = getChildByName<ParticleSystem*>("PS");
    if(ps) ps->setGravity(-getPhysicsBody()->getVelocity()*3.5f);
    
    if(state == StarEnergyState::Low) {
        //低能量，消失，游戏结束
        stop();
        setVisible(false);
        auto code = (void*)CustomEventCode::EnergyRanOut.c_str();
        _eventDispatcher->dispatchCustomEvent(CustomEventCode::JournalFinish, code);
    }
}

void MainStar::collisionMainStar(BaseStar* star)  {
    CCLOG("[MainStar] collisionMainStar will never happen");
}

void MainStar::collisionRoundStar(BaseStar* star) {
    CCLOG("[MainStar] collisionRoundStar");
    
    auto cur_energy = star->getEnergy();
    auto max_energy = star->getMaxEnergy();
    if(cur_energy > .8f*max_energy) {
        gainScore(1);
        gainEnergy(star->getMaxEnergy() * .20f);
    } else if(cur_energy > .5f*max_energy) {
        gainScore(2);
        gainEnergy(star->getMaxEnergy() * .15f);
    } else {
        gainScore(3);
        gainEnergy(star->getMaxEnergy() * .10f);
    }
}

void MainStar::collisionSquareStar(BaseStar* star)  {
    CCLOG("[MainStar] collisionSquareStar");
    explision(this, star);
    gainEnergy(-_maxEnergy * .01f);
}

void MainStar::collisionCosmicDust(BaseStar* star)  {
    CCLOG("[MainStar] collisionCosmicDust");
    auto v = getPhysicsBody()->getVelocity();
    getPhysicsBody()->setVelocity(v*.95f);
}

void MainStar::collisionPlanetStar(BaseStar* star)  {
    CCLOG("[MainStar] collisionPlanetStar");
    explision(this, star);
    gainEnergy(-_maxEnergy * .02f);
}

void MainStar::collisionStellarStar(BaseStar* star) {
    CCLOG("[MainStar] collisionStellarStar");
    explision(this, star);
    gainEnergy(-_energy);
}

void MainStar::collisionDipperStar(BaseStar* star)  {
    CCLOG("[MainStar] collisionDipperStar");
    
    explision(this, star);
    stop();
    setVisible(false);
    auto code = (void*)CustomEventCode::CompleteJournal.c_str();
    _eventDispatcher->dispatchCustomEvent(CustomEventCode::JournalFinish, code);
}

void MainStar::collisionMeteorStar(BaseStar* star) {
    CCLOG("[MainStar] collisionMeteorStar");
    gainEnergy(-star->getEnergy());
}
