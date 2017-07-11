//
//  ChapterScene.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "ChapterScene.hpp"
#include "GameTargetLayer.hpp"
#include "PauseControl.hpp"
#include "JoyStickLayer.hpp"
#include "FlowableBkgLayer.hpp"
#include "FlowableMoonObject.hpp"
#include "FireFlyObject.hpp"
#include "TimeUtilRef.h"

#define HIGH_ENERGY (80.f)
#define LOW_ENERGY (20.f)

#define UPTATE_FROM     (60)
#define UPDATE_SCALE    (4)
#define UPDATE_INTERVAL (60)
#define UPDATE_POW(t)   (UPTATE_FROM * pow(UPDATE_SCALE, t))

ChapterScene::ChapterScene() {
    _collisionLayer     = nullptr;
    _stackedLayer       = nullptr;
    _mainStar           = nullptr;
    _dipperStar         = nullptr;
    _contactListener    = nullptr;
    _updateCount = 0;
    _updateNum   = 1;
    _journalPeriod = .0f;
    
    removeAllChildren();
}

ChapterScene::~ChapterScene() {
    CCLOG("销毁释放");
}

bool ChapterScene::init() {
    if(!Scene::initWithPhysics()) {
        return false;
    }
    
    StarFactory::getInstance()->reset();
    StarFactory::getInstance()->limit(StarType::MainStar, 1);
    StarFactory::getInstance()->limit(StarType::DipperStar, 1);
    StarFactory::getInstance()->limit(StarType::RoundStar , 30);
    StarFactory::getInstance()->limit(StarType::SquareStar, 30);
    StarFactory::getInstance()->limit(StarType::MeteorStar, 30);
    StarFactory::getInstance()->limit(StarType::PlanetStar, 15);
    
    initPhysicsParams();
    initBackGroundLayer();
    initStackedLayer();
    openGameTargetLayer();
    
    return true;
}

void ChapterScene::initPhysicsParams() {
    auto physicConf = g_Service->getConfigInfo();
    if(physicConf->debugdraw) {
        _physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);
    }
    _physicsWorld->setGravity(Vec2(0, physicConf->gravity_y));
    _physicsWorld->setAutoStep(false);

    scheduleOnce([=](float delay) {
        _physicsWorld->setFixedUpdateRate(physicConf->updaterate);
    } , 1.f, SchedulerCode::OnceUpdatePhysicsWorld);
}

void ChapterScene::initBackGroundLayer() {
    auto flowable = FlowableBkgLayer::create();
    flowable->setBackgroundColor(COLOR_MAIN_BKG_4F);
    addChild(flowable, ZOrder::FlowableBackGround);
    
    // 飞月
//    auto moon = FlowableMoonObject::create();
//    addChild(moon, ZOrder::FlowableBackGround);
//    moon->moving();
    
    // 流萤
//    for (int i=0; i<8; i++) {
//        auto firefly = FireFlyObject::create();
//        addChild(firefly, ZOrder::FireFly);
//        firefly->fly();
//    }
}

void ChapterScene::initCollisionLayer() {
    auto collisionLayer = Layer::create();
    addChild(collisionLayer, ZOrder::CollisionLayer);
    _collisionLayer = collisionLayer;
    
    initMainStar();
//    initMotionStreak();
    initDipperStar();
    initEnergyBar();
}

void ChapterScene::initStackedLayer() {
    auto stacked = Layer::create();
    addChild(stacked, ZOrder::StackedLayer);
    _stackedLayer = stacked;
}

void ChapterScene::initJoyStick() {
    auto stick = JoyStickLayer::create();
    stick->bindMainStar(_mainStar);
    _stackedLayer->addChild(stick, ZOrder::JoyStick);
}

void ChapterScene::initPauseControl() {
    auto pause = PauseControl::create();
    _stackedLayer->addChild(pause, ZOrder::PauseControl);
}

void ChapterScene::initMainStar() {
    auto main = MainStar::create();
    main->setPosition(SCREEN_CENTER);
    main->setMoveScope(Vec2::ZERO);
    _mainStar = main;
    _mainStar->start();
    _collisionLayer->addChild(main, ZOrder::CollisionStar);
}

void ChapterScene::initEnergyBar() {
    auto size = Size(SCREEN_WIDTH, 120);
    auto half_height = size.height*.5;
    auto left_margin = 20;
    
    //背景
    auto barBG = Sprite::create("bar_energy_2.png");
    auto bsize = barBG->getContentSize();
    barBG->setColor(Color3B(18,143,144));
    barBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    barBG->setPosition(Vec2(left_margin, half_height));
    
    //前景
    auto fgSpr = Sprite::create("bar_energy_2.png");
    auto barFG = ProgressTimer::create(fgSpr);
    auto fsize = barFG->getContentSize();
    barFG->setType(cocos2d::ProgressTimer::Type::BAR);
    barFG->setMidpoint(Vec2(.0f,.5f));
    barFG->setBarChangeRate(Vec2(1.f, 0.f));
    barFG->setPositionX(left_margin+bsize.width*.5f);
    barFG->setPositionY(half_height);
    
    //能量文本
    auto energy = Label::createWithTTF("", FontMonitor::GAMEFONT, 10);
    energy->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    energy->setPosition(Vec2(barBG->getPositionX()+bsize.width*.5f, half_height));
    
    auto side_length = (SCREEN_WIDTH-left_margin*2-bsize.width) / 3.f;
    
    //时间
    auto time = Label::createWithTTF("", FontMonitor::GAMEFONT, 12);
    time->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    time->setPosition(Vec2(barBG->getPositionX()+bsize.width+left_margin+side_length*.5f, half_height));
    
    //距离
    auto distance = _dipperStar->getPosition().distance(_mainStar->getPosition());
    std::string coor_str = StringUtils::format(g_GetTextInfo(10).c_str(), distance);
    auto coor = Label::createWithTTF(coor_str, FontMonitor::GAMEFONT, 12);
    coor->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    coor->setPosition(Vec2(time->getPositionX()+side_length, half_height));
    
    //得分
    auto score_str = StringUtils::format(g_GetTextInfo(8).c_str(), 0);
    auto score = Label::createWithTTF(score_str, FontMonitor::GAMEFONT, 12);
    score->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    score->setPosition(Vec2(coor->getPositionX()+side_length, half_height));
    
    //添加
    auto bar = Node::create();
    bar->setContentSize(size);
    bar->addChild(barBG, 1, "back");
    bar->addChild(barFG, 2, "fore");
    bar->addChild(energy,3, "energy");
    bar->addChild(time , 3, "time");
    bar->addChild(coor , 4, "coor");
    bar->addChild(score, 5, "score");
    bar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    bar->setPositionX(0);
    bar->setPositionY(SCREEN_HEIGHT-18);
    _stackedLayer->addChild(bar, 10);
    _barContainer = bar;
}

void ChapterScene::updateEnergyBar() {
    if(_barContainer && _mainStar) {
        auto chapterInfo = g_Service->getChapterInfo(g_User->getCurPlayChapter());
        CCASSERT(chapterInfo!=nullptr, "chapter config must not be empty");
        
        //前景
        auto _energyBar = _barContainer->getChildByName<ProgressTimer*>("fore");
        if(!_energyBar) return;
        auto rate = _mainStar->getEnergy() / _mainStar->getMaxEnergy() * 100;
        auto color = Color3B(166,251,43);
        if(rate <= LOW_ENERGY) {
            color = Color3B(251,84,43);
        } else if(rate <= HIGH_ENERGY){
            color = Color3B(255,195,0);
        }
        _energyBar->getSprite()->setColor(color);
        _energyBar->setPercentage(rate);
        
        //背景
        auto _energyBarBg = _barContainer->getChildByName<Sprite*>("back");
        if(!_energyBarBg) return;
        if(rate <= chapterInfo->condition_energy) {
            if(_energyBarBg->getActionByTag(1) == nullptr) {
                auto t1 = TintTo::create(.2f, Color3B::WHITE);
                auto dt = DelayTime::create(.1f);
                auto t2 = TintTo::create(.2f, Color3B(18,143,144));
                auto sq = Sequence::create(t1, dt, t2, dt, NULL);
                auto act = RepeatForever::create(sq);
                act->setTag(1);
                _energyBarBg->runAction(act);
            }
        } else {
            _energyBarBg->stopActionByTag(1);
            _energyBarBg->setColor(Color3B(18,143,144));
        }
        
        //能量
        auto _energy = _barContainer->getChildByName<Label*>("energy");
        if(!_energy) return;
        _energy->setString(StringUtils::format("%.2f%%", _mainStar->getEnergy()/_mainStar->getMaxEnergy()*100));
        
        //时间
        auto _time = _barContainer->getChildByName<Label*>("time");
        if(!_time) return;
        auto isOverTime = (chapterInfo->condition_time == 0 || _journalPeriod < chapterInfo->condition_time);
        auto time = MAX(0, int(chapterInfo->condition_time-_journalPeriod+.5f));
        _time->setString(g_GetTextInfo(4)+std::string(TimeUtil::format(time)));
        _time->setColor(isOverTime ? Color3B::WHITE : Color3B::RED);

        //距离
        auto _coor = _barContainer->getChildByName<Label*>("coor");
        if(!_coor) return;
        auto distance = _dipperStar->getPosition().distance(_mainStar->getPosition());
        std::string coor_str = StringUtils::format(g_GetTextInfo(10).c_str(), distance);
        _coor->setString(coor_str);
        
        //得分
        auto _score = _barContainer->getChildByName<Label*>("score");
        if(!_score) return;
        _score->setString(StringUtils::format(g_GetTextInfo(8).c_str(), _mainStar->getScore()));
        
    }
}

void ChapterScene::initMotionStreak() {
    _mainStar->bindMotionStreak();
}

void ChapterScene::initDipperStar() {
    auto dipper = DipperStar::create();
    _collisionLayer->addChild(dipper, ZOrder::CollisionStar);
    _dipperStar = dipper;
}

void ChapterScene::openGameTargetLayer() {
    auto layer = GameTargetLayer::create();
    addChild(layer, ZOrder::GameTargetLayer);
}

void ChapterScene::openGameEndLayer(GameEndReason reason) {
    _stackedLayer->setVisible(false);
    unListenContact();
    
    JournalInfo info;
    info.reason = reason;
    info.chapterId = g_User->getCurPlayChapter();
    info.duration = _journalPeriod;
    info.score = _mainStar->getScore();
    info.energy = int(_mainStar->getEnergy() * _mainStar->getMaxEnergy() * 100);
    info.distance = reason == GameEndReason::CompleteJournal ? 0 : _dipperStar->getPosition().distance(_mainStar->getPosition());
    g_Game->setLatestJournalInfo(&info);
    
    auto endlayer = GameEndLayer::create();
    endlayer->open();
    this->addChild(endlayer, ZOrder::GameEndLayer);
}

void ChapterScene::onEnter() {
    Scene::onEnter();
    registerCustomEvent();
}

void ChapterScene::onListenContact() {
    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = [this](PhysicsContact& contact) {
        auto ca = (BaseStar*)contact.getShapeA()->getBody()->getNode();
        auto cb = (BaseStar*)contact.getShapeB()->getBody()->getNode();
        
        auto isContact = false;
        do {
            if(!ca || !cb) {
                isContact = false;
                break;
            }
            
            auto type1 = ca->getStarType(), type2 = cb->getStarType();
            
            if((type1 == StarType::MainStar   && type2 == StarType::DipperStar) ||
               (type1 == StarType::DipperStar && type2 == StarType::MainStar)) {
                _mainStar->collision(_dipperStar);
                isContact = true;
                break;
            } else if((type1 == StarType::MainStar  && type2 == StarType::RoundStar) ||
               (type1 == StarType::RoundStar && type2 == StarType::MainStar)) {
                auto round = static_cast<RoundStar*>(type1 == StarType::RoundStar ? ca : cb);
                _mainStar->collision(round);
                round->collision(_mainStar);
                isContact = true;
                break;
            } else if(type1 == StarType::MeteorStar || type2 == StarType::MeteorStar) {
                auto meteor = static_cast<MeteorStar*>(type1 == StarType::MeteorStar ? ca : cb);
                auto other = static_cast<BaseStar*>(type1 == StarType::MeteorStar ? cb : ca);
                other->collision(meteor);
                meteor->collision(other);
                isContact = true;
                break;
            } else if(type1 == StarType::SquareStar || type2 == StarType::SquareStar) {
                auto square = static_cast<SquareStar*>(type1 == StarType::SquareStar ? ca : cb);
                auto other = static_cast<BaseStar*>(type1 == StarType::SquareStar ? cb : ca);
                other->collision(square);
                square->collision(other);
                isContact = true;
                break;
            } else if(type1 == StarType::PlanetStar || type2 == StarType::PlanetStar) {
                auto planet = static_cast<PlanetStar*>(type1 == StarType::PlanetStar ? ca : cb);
                auto other = static_cast<BaseStar*>(type1 == StarType::PlanetStar ? cb : ca);
                other->collision(planet);
                planet->collision(other);
                isContact = true;
                break;
            } else if(type1 == StarType::DipperStar || type2 == StarType::DipperStar) {
                auto dipper = static_cast<DipperStar*>(type1 == StarType::DipperStar ? ca : cb);
                auto other = static_cast<BaseStar*>(type1 == StarType::DipperStar ? cb : ca);
                other->collision(dipper);
                dipper->collision(other);
                isContact = true;
                break;
            } else {
                CCLOG("Other Happens");
                ca->collision(cb);
                cb->collision(ca);
                isContact = false;
                break;
            }
        } while(0);

        return true;
        
    };
    _contactListener = listener;
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
}

void ChapterScene::unListenContact() {
    _mainStar->stop();
    unscheduleUpdate();
    unUpdateTimeCost();
}

void ChapterScene::onUpdateTimeCost() {
    schedule([this](float dt){
        _journalPeriod+= dt;
        updateEnergyBar();
    }, .1f, ClockRecord::JourneyDidFinish);
}

void ChapterScene::unUpdateTimeCost() {
    unschedule(ClockRecord::JourneyDidFinish);
}

void ChapterScene::registerCustomEvent() {
    
    //旅程开始
    _eventDispatcher->addCustomEventListener(CustomEventCode::StartJourney, [this](EventCustom* event) {
        if(!event->isStopped()) {
            initCollisionLayer();
            initJoyStick();
            initPauseControl();
            onListenContact();
            onUpdateTimeCost();
        }
    });
    
    //旅程结束
    _eventDispatcher->addCustomEventListener(CustomEventCode::JournalFinish, [this](EventCustom* event) {
        if(!event->isStopped()) {
            std::string code = std::string((const char*)event->getUserData());
            if(code == CustomEventCode::EnergyRanOut) {
                openGameEndLayer(GameEndReason::EnergyRanOut);
            } else if(code == CustomEventCode::PositiveExitJournal) {
                openGameEndLayer(GameEndReason::PositiveExitJournal);
            } else if(code == CustomEventCode::CompleteJournal) {
                openGameEndLayer(GameEndReason::CompleteJournal);
            } else if(code == CustomEventCode::DeadForStarExplosion) {
                openGameEndLayer(GameEndReason::DeadForStarExplosion);
            }
        }
    });
}

void ChapterScene::onExit() {
    unListenContact();
    
    _eventDispatcher->removeCustomEventListeners(CustomEventCode::StartJourney);
    _eventDispatcher->removeCustomEventListeners(CustomEventCode::JournalFinish);
    _eventDispatcher->removeEventListener(_contactListener);
    
    Scene::onExit();
}

void ChapterScene::generateStars(int num) {
    if(!_mainStar) return;
    
    auto pos = _mainStar->getPosition();
}

void ChapterScene::update(float dt) {
    for (int i = 0; i < 3; ++i) {
        _physicsWorld->step(1/180.0f);
    }
    
    if(!_mainStar || _mainStar->isPause() ||
       !_dipperStar || _dipperStar->isPause())
        return;
    
    _mainStar->update(dt);
    _dipperStar->update(dt);

//    CCLOG("count : %d, num : %d", _updateCount, _updateNum);
    
    auto pos = _mainStar->getPosition();
    _collisionLayer->runAction(Follow::create(_mainStar));
    
    // 前期星星增长快，后期限制数量
    if(     ++_updateCount == UPDATE_POW(0)) {
        _updateNum *= UPDATE_SCALE;
    } else if(_updateCount == UPDATE_POW(1)) {
        _updateNum *= UPDATE_SCALE;
    } else if(_updateCount == UPDATE_POW(2)) {
        _updateNum += UPDATE_SCALE;
    } else if(_updateCount == UPDATE_POW(3)) {
        _updateNum += UPDATE_SCALE;
    } else if(_updateCount == UPDATE_POW(4)) {
        _updateNum += UPDATE_SCALE;
    } else if(_updateCount == UPDATE_POW(5)) {
        _updateCount = 0;
        _updateNum = 1;
    }
    
    if(_updateCount % 10 == 0) {
        StarHelper::getRandomStar(_collisionLayer, pos, StarType::MeteorStar);
        StarHelper::getRandomStar(_collisionLayer, pos, StarType::RoundStar);
    }
    if(_updateCount % 20 == 0) {
        StarHelper::getRandomStar(_collisionLayer, pos, StarType::SquareStar);
    }
    if(_updateCount % 30 == 0) {
        StarHelper::getRandomStar(_collisionLayer, pos, StarType::PlanetStar);
    }
}

