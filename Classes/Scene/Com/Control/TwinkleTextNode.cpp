//
//  TwinkleTextNode.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#include "TwinkleTextNode.hpp"

bool TwinkleTextNode::init() {
    if(!Label::init()) {
        return false;
    }
    
    initWithTTF(g_GetTextInfo(7), FontMonitor::GAMEFONT, 12);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    setPosition(VisibleRectUtils::bottom()+Vec2(0,10));
    setOpacity(0);
    
    return true;
}

void TwinkleTextNode::fade() {
    stopAllActions();
    auto fat = .5f;
    auto fau = FadeIn::create(fat);
    auto fad = FadeOut::create(fat);
    auto dlt = DelayTime::create(.5f);
    auto seq = Sequence::create(fau, dlt, fad, NULL);
    runAction(RepeatForever::create(seq));
}

void TwinkleTextNode::onEnter() {
    Label::onEnter();
}

void TwinkleTextNode::onExit() {
    stopAllActions();
    Label::onExit();
}
