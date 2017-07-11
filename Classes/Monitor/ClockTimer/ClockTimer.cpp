//
//  ClockTimer.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/19.
//
//

#include "ClockTimer.hpp"

ClockTimer::~ClockTimer() {
    _vecClock.clear();
}

bool ClockTimer::init() {
    _vecClock.clear();
    
    return true;
}

T_ClockTimer* ClockTimer::newClock(std::string name) {
    T_ClockTimer* timer = new T_ClockTimer();
    timer->name = name;
    timer->running = true;
    timer->end = timer->begin = std::clock();
    
    return timer;
}

const T_ClockTimer* ClockTimer::getClock(std::string name) {
    auto it = _vecClock.begin();
    auto itd = _vecClock.end();
    for (; it != itd; it++) {
        if((*it)->name == name) {
            return (*it);
        }
    }

    return nullptr;
}

double ClockTimer::elapsed(std::string name) {
    auto it = _vecClock.begin();
    auto itd = _vecClock.end();
    for (; it != itd; it++) {
        if((*it)->name == name) {
            return double((*it)->end - (*it)->begin) / (double)CLOCKS_PER_SEC;;
        }
    }
    
    return 0;
}

void ClockTimer::start(std::string name, bool restart) {
    auto it = _vecClock.begin();
    auto itd = _vecClock.end();
    for (; it != itd; it++) {
        if((*it)->name == name) {
            if(!restart && (*it)->running) {
                CCLOG("%s is running.", name.c_str());
                return;
            }
            (*it)->running = true;
            (*it)->begin = (*it)->end = std::clock();
        }
    }
    
    _vecClock.push_back(newClock(name));
}

double ClockTimer::record(std::string name) {
    auto it = _vecClock.begin();
    auto itd = _vecClock.end();
    for (; it != itd; it++) {
        if((*it)->name == name) {
            auto now = std::clock();
            return double(now - (*it)->begin) / (double)CLOCKS_PER_SEC;
        }
    }
    return 0;
}

double ClockTimer::end(std::string name, bool shutdown) {
    auto it = _vecClock.begin();
    auto itd = _vecClock.end();
    for (; it != itd; it++) {
        if((*it)->name == name) {
            (*it)->running = false;
            (*it)->end = std::clock();
            auto diff = double((*it)->end - (*it)->begin) / (double)CLOCKS_PER_SEC;
            CCLOG("[ClockTimer] %s counts %.5fs.\n", name.c_str(), diff);
            if(shutdown) {
                _vecClock.erase(it);
            }
            return diff;
        }
    }
    
    return 0;
}

bool ClockTimer::shutdown(std::string name) {
    auto it = _vecClock.begin();
    auto itd = _vecClock.end();
    for (; it != itd; it++) {
        if((*it)->name == name) {
            _vecClock.erase(it);
            return true;
        }
    }
    
    return false;
}
