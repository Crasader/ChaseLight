//
//  GameTargetLayer.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/26.
//
//

#include "GameTargetLayer.hpp"
#include "VerticalTextNode.hpp"

bool GameTargetLayer::init() {
    if(!Layer::init()) {
        return false;
    }

    // 描述
    auto chapterId = g_User->getCurPlayChapter();
    auto chapterInfo = g_Service->getChapterInfo(chapterId);
    auto chapterDesc = g_GetTextInfo(chapterInfo->condition_text);
    auto labDesc = Label::createWithTTF(chapterDesc, FontMonitor::GAMEFONT, 14);
    labDesc->enableWrap(true);
    labDesc->setColor(Color3B(0,199,140));
    labDesc->setAlignment(cocos2d::TextHAlignment::CENTER);
    labDesc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    labDesc->setLineBreakWithoutSpace(true);
    labDesc->setLineSpacing(15.f);
    std::vector<Node*> alignNodes = {labDesc};//labTarget
    g_AlignScreenCenter(alignNodes, 15.f);
    addChild(labDesc);
    
    //箴言
    auto vertical = VerticalTextNode::create();
    vertical->setFontSize(12);
    vertical->setLineSpace(12.f);
    vertical->setText(g_GetTextInfo(chapterInfo->textId));
    vertical->setPosition(20.f, (SCREEN_HEIGHT+vertical->getContentSize().height)*.5f);
    vertical->fade();
    addChild(vertical);
    
    // 点击屏幕以继续
    _labTwinkle = TwinkleTextNode::create();
    addChild(_labTwinkle);
    
    // 延时可触摸
    auto duration = vertical->getDuration() + .2f;
    scheduleOnce([=](float dt) {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event) {
            return true;
        };
        listener->onTouchEnded = [=](Touch* touch, Event* event) {
            _eventDispatcher->dispatchCustomEvent(CustomEventCode::StartJourney);
            this->removeFromParentAndCleanup(true);
        };
        _listener = listener;
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
        
        _labTwinkle->fade();
        
    }, duration, SchedulerCode::OnceEnableLauchClick);
    
    return true;
}


void GameTargetLayer::onEnter() {
    Layer::onEnter();
}

void GameTargetLayer::onExit() {
    _eventDispatcher->removeEventListener(_listener);
    Layer::onExit();
}


