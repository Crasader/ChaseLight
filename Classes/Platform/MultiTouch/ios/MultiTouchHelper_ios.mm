//
//  MultiTouchHelper_ios.mm
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "MultiTouchHelper.hpp"
#include "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "RootViewController.h"

CCEAGLView* _getEaglView() {
    auto glview = cocos2d::Director::getInstance()->getOpenGLView();
    if (glview) {
        CCEAGLView *eaglview = (__bridge CCEAGLView *)glview->getEAGLView();
        if (eaglview) {
            return eaglview;
        }
    }
    return nullptr;
}

void setMultiTouchEnabled(bool isOpen){
    CCEAGLView* view = _getEaglView();
    if(!view) return;
    [view setMultipleTouchEnabled:isOpen];
}

bool isMultiTouchEnabled() {
    CCEAGLView* view = _getEaglView();
    if(!view) return false;
    return [view isMultipleTouchEnabled];
}

