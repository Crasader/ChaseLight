//
//  ClockTimer.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//  Comment : 可用于开发测试，在真机上时间不太准，偏慢

#ifndef ClockTimer_hpp
#define ClockTimer_hpp

#include <cocos2d.h>
#include <ctime>
#include "Singleton.hpp"
using namespace std;
USING_NS_CC;

namespace ClockRecord {
    static std::string GameDidFinish     = "Game";
    static std::string JourneyDidFinish  = "Journey";
    static std::string ServiceDidLauch   = "Service";
}

struct T_ClockTimer {
    bool running;
    std::string name;
    std::clock_t begin;
    std::clock_t end;
};

class ClockTimer : public Singleton<ClockTimer> {
public:
    ~ClockTimer();
    bool init() override;
    void start(std::string name, bool restart=false);
    double record(std::string name);
    double end(std::string name, bool shutdown=false);
    const T_ClockTimer* getClock(std::string name);
    double elapsed(std::string name);
    bool shutdown(std::string name);
    
private:
    T_ClockTimer* newClock(std::string name="");
    std::vector<T_ClockTimer*> _vecClock;
};

#endif /* ClockTimer_hpp */
