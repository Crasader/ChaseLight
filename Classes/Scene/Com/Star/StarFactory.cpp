//
//  StarFactory.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/28.
//
//

#include "StarFactory.hpp"

StarFactory* StarFactory::_instance = nullptr;

StarFactory::StarFactory()
: _counter(nullptr)
{
    _counter = new StartCounter();
    _counter->reset();
    _counter->resetLimit();
}

StarFactory::~StarFactory() {
    
}

bool StarFactory::init(int nRoundStarLimit,   int nSquareStarLimit,
                       int nCosmicDustLimit,  int nPlanetStarLimit,
                       int nStellarStarLimit, int nMeteorStarLimit)
{
    _counter->nRoundStarLimit   = nRoundStarLimit;
    _counter->nSquareStarLimit  = nSquareStarLimit;
    _counter->nCosmicDustLimit  = nCosmicDustLimit;
    _counter->nPlanetStarLimit  = nPlanetStarLimit;
    _counter->nStellarStarLimit = nStellarStarLimit;
    _counter->nMeteorStarLimit  = nMeteorStarLimit;
    
    return true;
}

bool StarFactory::increase(StarType type) {
    bool ret = false;
    switch (type) {
        case StarType::MainStar:
        {
            CC_BREAK_IF(_counter->nMainStar >= _counter->nMainStarLimit);
            _counter->nMainStar += 1;
            ret = true;
        }
            break;
            
        case StarType::RoundStar:
        {
            CC_BREAK_IF(_counter->nRoundStar >= _counter->nRoundStarLimit);
            _counter->nRoundStar += 1;
            ret = true;
        }
            break;
            
        case StarType::CosmicDust :
        {
            CC_BREAK_IF(_counter->nCosmicDust >= _counter->nCosmicDustLimit);
            _counter->nCosmicDust += 1;
            ret = true;
        }
            break;
            
        case StarType::MeteorStar :
        {
            CC_BREAK_IF(_counter->nMeteorStar >= _counter->nMeteorStarLimit);
            _counter->nMeteorStar += 1;
            ret = true;
        }
            break;
            
        case StarType::SquareStar :
        {
            CC_BREAK_IF(_counter->nSquareStar >= _counter->nSquareStarLimit);
            _counter->nSquareStar += 1;
            ret = true;
        }
            break;
            
        case StarType::StellarStar:
        {
            CC_BREAK_IF(_counter->nStellarStar >= _counter->nStellarStarLimit);
            _counter->nStellarStar += 1;
            ret = true;
        }
            break;
            
        case StarType::DipperStar :
        {
            CC_BREAK_IF(_counter->nDipperStar >= _counter->nDipperStarLimit);
            _counter->nDipperStar += 1;
            ret = true;
        }
            break;
            
        case StarType::PlanetStar:
        {
            CC_BREAK_IF(_counter->nPlanetStar >= _counter->nPlanetStarLimit);
            _counter->nPlanetStar += 1;
            ret = true;
        }
            break;
            
        case StarType::None:
        default:
        {
            
            ret = false;
        }
            break;
    }
    
    return ret;
}

bool StarFactory::decrease(StarType type) {
    bool ret = false;
    switch (type) {
        case StarType::MainStar:
        {
            CC_BREAK_IF(_counter->nMainStar <= 0);
            _counter->nMainStar -= 1;
            ret = true;
        }
            break;
            
        case StarType::RoundStar:
        {
            CC_BREAK_IF(_counter->nRoundStar <= 0);
            _counter->nRoundStar -= 1;
            ret = true;
        }
            break;
            
        case StarType::CosmicDust :
        {
            CC_BREAK_IF(_counter->nCosmicDust <= 0);
            _counter->nCosmicDust -= 1;
            ret = true;
        }
            break;
            
        case StarType::MeteorStar :
        {
            CC_BREAK_IF(_counter->nMeteorStar <= 0);
            _counter->nMeteorStar -= 1;
            ret = true;
        }
            break;
            
        case StarType::SquareStar :
        {
            CC_BREAK_IF(_counter->nSquareStar <= 0);
            _counter->nSquareStar -= 1;
            ret = true;
        }
            break;
            
        case StarType::StellarStar:
        {
            CC_BREAK_IF(_counter->nStellarStar <= 0);
            _counter->nStellarStar -= 1;
            ret = true;
        }
            break;
            
        case StarType::DipperStar :
        {
            CC_BREAK_IF(_counter->nDipperStar <= 0);
            _counter->nDipperStar -= 1;
            ret = true;
        }
            break;
            
        case StarType::PlanetStar:
        {
            CC_BREAK_IF(_counter->nPlanetStar <= 0);
            _counter->nPlanetStar -= 1;
            ret = true;
        }
            break;
            
        case StarType::None:
        default:
        {
            ret = false;
        }
            break;
    }
    
    return ret;
}

int StarFactory::count(StarType type) {
    switch (type) {
        case StarType::MainStar:
        {
            return _counter->nMainStar;
        }
            
        case StarType::RoundStar:
        {
            return _counter->nRoundStar;
        }
            
        case StarType::CosmicDust :
        {
            return _counter->nCosmicDust;
        }
            
        case StarType::MeteorStar :
        {
            return _counter->nMeteorStar;
        }
            
        case StarType::SquareStar :
        {
            return _counter->nSquareStar;
        }
            
        case StarType::StellarStar:
        {
            return _counter->nStellarStar;
        }
            
        case StarType::DipperStar :
        {
            return _counter->nDipperStar;
        }
            
        case StarType::PlanetStar:
        {
            return _counter->nPlanetStar;
        }
            
        case StarType::None:
        default:
        {
            return 0;
        }
    }

    return 0;
}

bool StarFactory::limit(StarType type, int newlimit) {
    bool ret = false;
    switch (type) {
        case StarType::RoundStar:
        {
            _counter->nRoundStarLimit = newlimit;
            ret = true;
        }
            break;
            
        case StarType::CosmicDust :
        {
            _counter->nCosmicDustLimit = newlimit;
            ret = true;
        }
            break;
            
        case StarType::MeteorStar :
        {
            _counter->nMeteorStarLimit = newlimit;
            ret = true;
        }
            break;
            
        case StarType::SquareStar :
        {
            _counter->nSquareStarLimit = newlimit;
            ret = true;
        }
            break;
            
        case StarType::StellarStar:
        {
            _counter->nStellarStarLimit = newlimit;
            ret = true;
        }
            break;
            
        case StarType::PlanetStar:
        {
            _counter->nPlanetStarLimit = newlimit;
            ret = true;
        }
            break;
            
        case StarType::None:
        case StarType::MainStar:
        case StarType::DipperStar:
        default:
            ret = false;
            break;
    }
    
    return ret;
}

int StarFactory::total() {
    return _counter->total();
}

void StarFactory::reset() {
    _counter->reset();
}
