//
//  MainStar.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/27.
//
//

#ifndef MainStar_hpp
#define MainStar_hpp

#include "BaseStar.hpp"

class MainStar : public BaseStar {
public:
    MainStar();
    ~MainStar();
    CREATE_FUNC(MainStar);
    
    bool init() override;
    void behaviour(StarEnergyState state) override;
    void update(float dt) override;
    void setMoveScope(Vec2 speed) override;
    void collisionMainStar(BaseStar* star) override;
    void collisionRoundStar(BaseStar* star) override;
    void collisionSquareStar(BaseStar* star) override;
    void collisionCosmicDust(BaseStar* star) override;
    void collisionPlanetStar(BaseStar* star) override;
    void collisionStellarStar(BaseStar* star) override;
    void collisionDipperStar(BaseStar* star) override;
    void collisionMeteorStar(BaseStar* star) override;
    inline int getScore() { return _score; }
    inline void gainScore(int score) { _score += score; };
    
private:
    int _score = 0;
};

#endif /* MainStar_hpp */
