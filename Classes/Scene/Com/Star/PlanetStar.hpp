//
//  PlanetStar.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#ifndef PlanetStar_hpp
#define PlanetStar_hpp

#include "BaseStar.hpp"
#include "StarFactory.hpp"

class PlanetStar : public BaseStar {
public:
    PlanetStar();
    ~PlanetStar();
    CREATE_FUNC(PlanetStar);
    bool init() override;
    void behaviour(StarEnergyState state) override;
    void update(float dt) override;
    void bigBoom();
    
    void collisionMainStar(BaseStar* star) override;
    void collisionRoundStar(BaseStar* star) override;
    void collisionPlanetStar(BaseStar* star) override;
    void collisionCosmicDust(BaseStar* star) override;
    void collisionSquareStar(BaseStar* star) override;
    void collisionStellarStar(BaseStar* star) override;
    void collisionDipperStar(BaseStar* star) override;
    void collisionMeteorStar(BaseStar* star) override;
};

#endif /* PlanetStar_hpp */
