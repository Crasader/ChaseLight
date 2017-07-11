//
//  StartScene.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include "CCBase.h"
#include "FlowableBkgLayer.hpp"
#include "ChapterPageView.hpp"

class StartScene final : public Scene {
public:
    bool init() override;
    CREATE_FUNC(StartScene);
    
    void onEnter() override;
    
protected:
    StartScene();
    ~StartScene();

private:
    ChapterPageView* _chapter = nullptr;
    Sprite* _cloud = nullptr;
};

#endif /* StartScene_hpp */
