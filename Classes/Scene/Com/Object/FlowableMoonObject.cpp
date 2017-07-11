//
//  FlowableMoonObject.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/25.
//
//

#include "FlowableMoonObject.hpp"
#define kClipperTag (10)
#define kMoonTag (20)

bool FlowableMoonObject::init() {
    if(!Node::init()) {
        return false;
    }
    
    // 模板
    auto stencil = Sprite::create("star_moon.png");
    stencil->retain();
    auto size = stencil->getContentSize();
    setContentSize(size);
    
    // 画板
    auto clipper = ClippingNode::create();
    clipper->setContentSize(size);
    clipper->setAlphaThreshold(.1f);
    clipper->setStencil(stencil);
    clipper->setInverted(false);
    stencil->setColor(COLOR_MOON);
    clipper->addChild(stencil);
    
    // 裁切
    auto moon = Sprite::create("star_moon.png");
    moon->setPosition(Vec2::ZERO);
    moon->setColor(COLOR_MAIN_BKG_3B);
    moon->setTag(kMoonTag);
    clipper->addChild(moon);
    clipper->setTag(kClipperTag);
    addChild(clipper);
    
    return true;
}

void FlowableMoonObject::moving() {
    auto size = SCREEN_SIZE;
    auto msize = getContentSize();
    auto fromPos = Vec2(-msize.width, size.height * .3f);
    auto endPos = Vec2(size.width+msize.width, size.height * .5f);
    setPosition(fromPos);
    
    // 月亮的影子
    auto moon = getChildByTag(kClipperTag)->getChildByTag(kMoonTag);
    auto time1 = size.width;
    auto time2 = time1/60.f;
    auto mov = MoveBy::create(time1, Vec2(msize.width, msize.height));
    auto dlt = DelayTime::create(time2);
    auto seq_moon_shadow = Sequence::create(mov, dlt, mov->reverse(), dlt, NULL);
    moon->runAction(RepeatForever::create(seq_moon_shadow));
    
    
    // 月亮的移动
    auto bezier = ccBezierConfig();
    bezier.controlPoint_1 = Vec2(size.width*.35f, size.height*.78f);
    bezier.controlPoint_2 = Vec2(size.width*.65f, size.height*.75f);
    bezier.endPosition = endPos;
    
    auto bezier2 = ccBezierConfig();
    bezier2.controlPoint_1 = Vec2(size.width*.85f, size.height*.25f);
    bezier2.controlPoint_2 = Vec2(size.width*.15f, size.height*.05f);
    bezier2.endPosition = fromPos;
    
    auto bez = BezierTo::create(time1, bezier);
    auto bez2 = BezierTo::create(time1, bezier2);
    auto seq_moon_move = Sequence::create(bez, dlt, bez2, dlt, nullptr);
    runAction(RepeatForever::create(seq_moon_move));
}
