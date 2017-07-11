//
//  RoundStar.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#ifndef RoundStar_hpp
#define RoundStar_hpp

#include "BaseStar.hpp"

class RoundStar : public BaseStar {
public:
    RoundStar();
    ~RoundStar();
    CREATE_FUNC(RoundStar);
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

#endif /* RoundStar_hpp */
