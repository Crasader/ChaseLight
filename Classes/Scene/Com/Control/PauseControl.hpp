//
//  PauseControl.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/20.
//
//

#ifndef PauseControl_hpp
#define PauseControl_hpp

#include "CCBase.h"

class PauseControl : public Layout {
public:
    bool init() override;
    CREATE_FUNC(PauseControl);
    void onEnter() override;
    void onExit() override;
    
private:
    Button* _btnBack = nullptr;
    Button* _btnStop = nullptr;
    Label* _labStop = nullptr;
    EventListenerTouchOneByOne* _listener = nullptr;
    bool _isMoved = false;
    
private:
    void updateState(bool pause);
};

#endif /* PauseControl_hpp */
