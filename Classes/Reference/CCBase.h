//
//  CCBase.h
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef CCBase_h
#define CCBase_h

// 原生引擎
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d::experimental;
using namespace std;

// 扩展
#include "StructRef.h"
#include "VisibleRectUtils.hpp"
#include "RandomGeometryCom.hpp"
#include "Game.hpp"
#include "ServicePack.hpp"
#include "FontMonitor.h"
#include "ClockTimer.hpp"
#include "AudioMonitor.hpp"
#include "ZOrderRef.h"
#include "EventCodeRef.h"
#include "SchedulerRef.h"
#include "CollisionTagRef.h"
#include "UserDataService.hpp"

// 判断浮点数是否为0
#define ZEROF(f) (f<0.000001f && f>-0.000001f)
#define NAGATIVEF(f) (f<=-0.000001f)
#define POSITIVEF(f) (f>=0.000001f)

// 单例
#define g_Director      Director::getInstance()
#define g_Game          Game::getInstance()
#define g_Service       ServicePack::getInstance()
#define g_ClockTimer    ClockTimer::getInstance()
#define g_Audio         AudioMonitor::getInstance()
#define g_User          UserDataService::getInstance()

// 获取文本
#define g_GetTextInfo(textId)   ServicePack::getInstance()->getTextInfo(textId)
#define TEXT_SEC  (g_GetTextInfo(500).c_str())
#define TEXT_MIN  (g_GetTextInfo(501).c_str())
#define TEXT_HOU  (g_GetTextInfo(502).c_str())
#define TEXT_DAY  (g_GetTextInfo(503).c_str())

// 颜色
#define COLOR_MAIN_BKG_3B   Color3B(11,23,70)
#define COLOR_MAIN_BKG_4F   Color4F(Color3B(11,23,70), 1.0f)
#define COLOR_MOON          Color3B(255,235,205)
#define COLOR_MAIN_BTN_TEXT Color3B(50,205,50)

// 屏幕
#define SCREEN_SIZE         VisibleRectUtils::visibleRect().size
#define SCREEN_WIDTH        VisibleRectUtils::visibleRect().size.width
#define SCREEN_HEIGHT       VisibleRectUtils::visibleRect().size.height
#define SCREEN_CENTER       VisibleRectUtils::center()
#define SCREEN_CENTER_X     VisibleRectUtils::center().x
#define SCREEN_CENTER_Y     VisibleRectUtils::center().y

//对屏幕居中对齐
static void g_AlignScreenCenter(const std::vector<Node*> &v, float linespace = 0.f) {
    auto all_height = 0.f;
    for(auto node : v) {
        all_height += node->getContentSize().height + linespace;
    }
    
    auto from = (SCREEN_HEIGHT + all_height) * .5f;
    for(auto node : v) {
        node->setPositionX(SCREEN_CENTER_X);
        node->setPositionY(from);
        from -= node->getContentSize().height + linespace;
    }
}

#endif /* CCBase_h */
