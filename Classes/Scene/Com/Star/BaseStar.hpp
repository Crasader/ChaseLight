//
//  BaseStar.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef BaseStar_hpp
#define BaseStar_hpp

#include "CCBase.h"
#include "StarFactory.hpp"
#define COMPONENT_PHYSICS_BODY ("PhysicsBody")

enum class StarEnergyState {
    Low,
    Normal,
    Full
};

class BaseStar : public Sprite {
public:
    BaseStar();
    virtual ~BaseStar();
    CREATE_FUNC(BaseStar);

    void stop();
    void start();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    virtual void behaviour();
    virtual void behaviour(StarEnergyState state);
    virtual bool gainEnergy(float energy);
    virtual bool isLow();
    virtual bool isFull();
    
    void updateScale();
    void collision(BaseStar* star);
    virtual void collisionMainStar(BaseStar* star);
    virtual void collisionRoundStar(BaseStar* star);
    virtual void collisionSquareStar(BaseStar* star);
    virtual void collisionCosmicDust(BaseStar* star);
    virtual void collisionPlanetStar(BaseStar* star);
    virtual void collisionStellarStar(BaseStar* star);
    virtual void collisionDipperStar(BaseStar* star);
    virtual void collisionMeteorStar(BaseStar* star);
    
    virtual inline bool isPause()   { return _pause; }
    inline float getEnergy()        { return _energy; }
    inline float getMaxEnergy()     { return _maxEnergy; }
    inline Vec2 getMoveScope()      { return _moveScope; };
    inline StarType getStarType()   { return _starType; }
    virtual inline void setMoveScope(Vec2 scope) { _moveScope = scope; }
    
    void checkStreak(float dt);
    void bindMotionStreak(); //需要在星星添加到场景后操作
    
    
protected:
    MotionStreak* _streak = nullptr;
    StarType _starType = StarType::None;
    std::string _texurefile = "";   //纹理文件
    float _energy    = 0.f; //初始能量
    float _maxEnergy = 0.f; //最大能量
    float _secEnergy = 1.f; //每秒减能量
    float _maxScale  = 5.f; //最大缩放系数
    float _minScale  = .5f; //最小缩放系数
    float _maxMoveRadius = .0f; //最大活动半径，初始化的时候在此范围内随机，获得当前活动范围
    Vec2 _moveScope  = Vec2::ZERO; //当前活动范围
    bool _pause = true;
};


static void explision(Node* star1, Node* star2) {
    auto lw = star1->getContentSize().width * star1->getScale();
    auto R = lw / 2 * .4f;
    auto parent = star1->getParent();
    auto off = star2->getPhysicsBody()->getVelocity()-star1->getPhysicsBody()->getVelocity();
    for(int i=0; i<3; i++) {
        auto pos = star1->getPosition();
        auto theta = RandomHelper::random_real(0.f, 2.f*3.1415926f);
        auto k = random(0.f, 1.f);
        auto d = sqrt(k)*R;
        auto x = d*sin(theta);
        auto y = d*cos(theta);
        auto node = Sprite::create("star_round_2x.png");//"firefly.png"
        auto wp = star1->getPosition();
        node->setColor(star1->getColor());
        parent->addChild(node,1);
        node->setPosition(wp+Vec2(x,y)+(star2->getPosition()-wp)/2);
        node->setOpacity(50);
        auto tim = MIN(.8f, star1->getScale() * star2->getScale());
        auto mvb = (off) / random(25.f, 50.f);
        auto fad = FadeOut::create(tim);
        auto mov = MoveBy::create(tim, mvb);
        auto spw = Spawn::create(fad, mov, NULL);
        auto rmv = RemoveSelf::create();
        node->runAction(Sequence::create(spw, rmv, NULL));
    }
}


#endif /* BaseStar_hpp */
