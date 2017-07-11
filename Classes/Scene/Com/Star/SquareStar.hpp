//
//  SquareStar.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#ifndef SquareStar_hpp
#define SquareStar_hpp

#include "BaseStar.hpp"
#include "StarFactory.hpp"

class SquareStar : public BaseStar {
public:
    SquareStar();
    ~SquareStar();
    CREATE_FUNC(SquareStar);
    bool init() override;
    void behaviour(StarEnergyState state) override;
    void update(float dt) override;
    
    void collisionMainStar(BaseStar* star) override;
    void collisionRoundStar(BaseStar* star) override;
    void collisionSquareStar(BaseStar* star) override;
    void collisionCosmicDust(BaseStar* star) override;
    void collisionPlanetStar(BaseStar* star) override;
    void collisionStellarStar(BaseStar* star) override;
    void collisionDipperStar(BaseStar* star) override;
    void collisionMeteorStar(BaseStar* star) override;
};


#endif /* SquareStar_hpp */
