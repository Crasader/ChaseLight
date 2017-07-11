//
//  StartScene.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#include "StartScene.hpp"
#include "TouchLayer.hpp"
#include "FlowableBkgLayer.hpp"
#include "ChapterScene.hpp"
#include "RandomGeometryCom.hpp"
#include "FlowCloudObject.hpp"
#include "FlowableMoonObject.hpp"
#include "FireFlyObject.hpp"

StartScene::StartScene() {
    _chapter  = nullptr;
    _cloud = nullptr;
}

StartScene::~StartScene() {
    
}

bool StartScene::init() {
    auto center = SCREEN_CENTER;
    auto size = SCREEN_SIZE;
    
    initWithPhysics();
    getPhysicsWorld()->setGravity(Vec2(0, -20));
    
    //触屏
    addChild(TouchLayer::create(), ZOrder::Touch);
    
    //流动的背景
    auto flowable = FlowableBkgLayer::create();
    flowable->setBackgroundColor(COLOR_MAIN_BKG_4F);
    addChild(flowable, ZOrder::FlowableBackGround);
    
    //流动的云朵
//    auto cloud = FlowCloudObject::create();
//    cloud->setPosition(center);
//    addChild(cloud, ZOrder::FlowableCloud);
//    _cloud = cloud;
    
    // 飞月
    auto moon = FlowableMoonObject::create();
    addChild(moon, ZOrder::FlowableBackGround);
    moon->moving();
//
//    // 流萤
//    for (int i=0; i<16; i++) {
//        auto firefly = FireFlyObject::create();
//        addChild(firefly, ZOrder::FireFly);
//        firefly->fly();
//    }

    //翻页章节
    auto chapter = ChapterPageView::create();
    addChild(chapter, ZOrder::ChapterPageView);
    _chapter = chapter;
    
    return true;
}

void StartScene::onEnter() {
    Scene::onEnter();
    _chapter->reload();
    _chapter->setChapter(g_User->getCurPlayChapter());
}
