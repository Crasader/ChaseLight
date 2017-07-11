//
//  DipperStar.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#ifndef DipperStar_hpp
#define DipperStar_hpp

#include "BaseStar.hpp"

class DipperStar : public BaseStar {
public:
    DipperStar();
    ~DipperStar();
    CREATE_FUNC(DipperStar);
    
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

#endif /* DipperStar_hpp */
