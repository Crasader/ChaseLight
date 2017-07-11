//
//  PauseControl.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/20.
//
//

#define kStopTag (1000)
#define SIDE_WIDTH (60)
#define SIDE_HEIGHT (20)
#define MENU_SPRITE_TAG (1)
#define MENU_LABEL_TAG  (2)
#include "PauseControl.hpp"

static Node* getMenuItem(int textId, const Color3B &color=Color3B::WHITE) {
    
    auto sprite = Sprite::create("star_4x.png");
    sprite->setColor(color);
    sprite->setTag(MENU_SPRITE_TAG);
    
    return sprite;
}

bool PauseControl::init() {
    if(!Layout::init()) {
        return false;
    }
    
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    auto item1 = MenuItemLabel::create(getMenuItem(2, Color3B::YELLOW), [=](Ref* sender){
        auto item = (MenuItemLabel*)sender;
        auto node = item->getLabel();
        if(node->getTag() == MENU_SPRITE_TAG) {
            auto pause = _director->isPaused();
            node = (Sprite*)node;
            node->setColor(pause ? Color3B::YELLOW : Color3B::LIGHTGREEN);
            pause ? _director->resume() : _director->pause();
        }
    });
    auto item2 = MenuItemLabel::create(getMenuItem(4, Color3B::RED), [=](Ref* sender){
        _director->resume();
        _eventDispatcher->dispatchCustomEvent(CustomEventCode::JournalFinish, (void*)CustomEventCode::PositiveExitJournal.c_str());
    });
    
    auto padding = 5;
    auto itemSize = item1->getContentSize();
    auto menuSize = Size(itemSize.width+padding*2, (itemSize.height*2+padding*3));
    auto menu = Menu::create(item1, item2, nullptr);
    setContentSize(menuSize);
    menu->setContentSize(menuSize);
    menu->alignItemsVerticallyWithPadding(padding);
    menu->setPosition(Vec2(menuSize.width, menuSize.height)*.5f);
    addChild(menu);
    
    setPosition(Vec2(menuSize.width*.5f, SCREEN_CENTER.y));

    setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    setBackGroundColor(Color3B::AQUA);
    setBackGroundColorOpacity(20);
    
    return true;
}

void PauseControl::updateState(bool pause) {

}

void PauseControl::onEnter() {
    Layout::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        auto np = this->getPosition();
        auto sz = this->getContentSize();
        auto rect = Rect(-sz.width*.5f, -sz.height*.5f, sz.width, sz.height);
        return rect.containsPoint(pos-np);
    };
    listener->onTouchMoved = [=](Touch* touch, Event* event) {
        this->_isMoved = true;
        this->setPosition(touch->getLocation());
    };
    listener->onTouchCancelled = listener->onTouchEnded = [=](Touch* touch, Event* event) {
        if(!this->_isMoved) {
            return;
        }
        auto pos = touch->getLocation();
        auto sz = this->getContentSize();
        auto hw = sz.width *.5f, hh = sz.height*.5f;
        auto px = pos.x > SCREEN_WIDTH*.5f ? SCREEN_WIDTH-hw : hw;
        auto py = pos.y > SCREEN_HEIGHT-hh ? SCREEN_HEIGHT-hh : (pos.y < hh ? hh : pos.y);
        this->setPosition(Vec2(px, py));
        _isMoved = false;
    };
    _listener = listener;
    _listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void PauseControl::onExit() {
    _eventDispatcher->removeEventListener(_listener);
    Layout::onExit();
}
