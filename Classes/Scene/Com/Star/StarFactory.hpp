//
//  StarFactory.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/28.
//
//

#ifndef StarFactory_hpp
#define StarFactory_hpp

#include "CCBase.h"

enum class StarType {
    None,
    MainStar,
    RoundStar,
    SquareStar,
    CosmicDust,
    PlanetStar,
    StellarStar,
    DipperStar,
    MeteorStar,
};

struct StartCounter {
    int nMainStar;
    int nRoundStar;
    int nSquareStar;
    int nCosmicDust;
    int nPlanetStar;
    int nStellarStar;
    int nDipperStar;
    int nMeteorStar;
    
    int nMainStarLimit;
    int nRoundStarLimit;
    int nSquareStarLimit;
    int nCosmicDustLimit;
    int nPlanetStarLimit;
    int nStellarStarLimit;
    int nDipperStarLimit;
    int nMeteorStarLimit;
    
    StartCounter() {
        nMainStar = 0;
        nRoundStar = 0;
        nSquareStar = 0;
        nCosmicDust = 0;
        nPlanetStar = 0;
        nStellarStar = 0;
        nDipperStar = 0;
        nMeteorStar = 0;
        
        nMainStarLimit = 1;
        nRoundStarLimit = 10;
        nSquareStarLimit = 10;
        nCosmicDustLimit = 10;
        nPlanetStarLimit = 10;
        nStellarStarLimit = 10;
        nDipperStarLimit = 7;
        nMeteorStarLimit = 10;
    }
    
    void reset() {
        nMainStar = 0;
        nRoundStar = 0;
        nSquareStar = 0;
        nCosmicDust = 0;
        nPlanetStar = 0;
        nStellarStar = 0;
        nDipperStar = 0;
        nMeteorStar = 0;
    }
    
    void resetLimit() {
        nMainStarLimit = 1;
        nRoundStarLimit = 10;
        nSquareStarLimit = 10;
        nCosmicDustLimit = 10;
        nPlanetStarLimit = 10;
        nStellarStarLimit = 10;
        nDipperStarLimit = 7;
        nMeteorStarLimit = 10;
    }
    
    int total() {
        return (nMainStar + nRoundStar
        + nSquareStar + nCosmicDust
        + nPlanetStar + nStellarStar
        + nDipperStar + nMeteorStar);
    }
};

class StarFactory {
private:
    static StarFactory* _instance;
    StartCounter* _counter = nullptr;
    
public:
    StarFactory();
    ~StarFactory();
    
    static StarFactory* getInstance() {
        if(!_instance) {
            _instance = new StarFactory();
            _instance->init();
        }
        return _instance;
    }
    
    bool init(int nRoundStarLimit  = 10,
              int nSquareStarLimit = 10,
              int nCosmicDustLimit = 10,
              int nPlanetStarLimit = 10,
              int nStellarStarLimit= 10,
              int nMeteorStarLimit = 10);
    
    bool increase(StarType type);
    bool decrease(StarType type);
    bool limit(StarType type, int newlimit);
    int count(StarType type);
    int total();
    void reset();
};

#endif /* StarFactory_hpp */
