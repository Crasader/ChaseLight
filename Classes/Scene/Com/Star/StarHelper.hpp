//
//  StarHelper.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/6.
//
//

#ifndef StarHelper_h
#define StarHelper_h

#include "StarFactory.hpp"
#include "BaseStar.hpp"
#include "RoundStar.hpp"
#include "MainStar.hpp"
#include "MeteorStar.hpp"
#include "DipperStar.hpp"
#include "SquareStar.hpp"
#include "PlanetStar.hpp"

namespace StarHelper {
    static const std::vector<StarType> _Stars_ = {
        StarType::RoundStar,
        StarType::MeteorStar,
        StarType::SquareStar,
        StarType::PlanetStar
    };
    
    static void getRandomStar(Node* container, Vec2 pos, StarType type=StarType::None, int num=1) {
        for(int i=0; i<num; i++) {
            auto t = type != StarType::None ? type : _Stars_[random(0, (int)_Stars_.size()-1)];
            BaseStar* star = nullptr;
            
            switch (t) {
                case StarType::RoundStar:
                    star = RoundStar::create();
                    break;
                    
                case StarType::MeteorStar:
                    star = MeteorStar::create();
                    break;
                    
                case StarType::SquareStar:
                    star = SquareStar::create();
                    break;
                    
                case StarType::PlanetStar:
                    star = PlanetStar::create();
                    break;
                    
                default:
                    break;
            }
            
            if(!star) continue;
            auto v = pos + star->getPosition() - SCREEN_CENTER;
            star->setPosition(v);
            container->addChild(star, ZOrder::CollisionStar);
        }
    }
    
    static void collision(BaseStar* star1, BaseStar* star2) {
        auto type1 = star1->getStarType(), type2 = star2->getStarType();
        
        if((type1 == StarType::MainStar   && type2 == StarType::DipperStar) ||
           (type1 == StarType::DipperStar && type2 == StarType::MainStar)) {
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CustomEventCode::JournalFinish, (void*)CustomEventCode::CompleteJournal.c_str());
        }
        
        if((type1 == StarType::MainStar  && type2 == StarType::RoundStar) ||
           (type1 == StarType::RoundStar && type2 == StarType::MainStar)) {
            auto round = static_cast<RoundStar*>(type1 == StarType::RoundStar ? star1 : star2);
            auto main  = static_cast<MainStar*>(type1 == StarType::MainStar ? star1 : star2);
            main->collisionRoundStar(round);
            round->collisionMainStar(main);
        }
    }
}



#endif /* StarHelper_hpp */
