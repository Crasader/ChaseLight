//
//  VisibleRectUtils.hpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/18.
//
//

#ifndef VisibleRectUtils_hpp
#define VisibleRectUtils_hpp

#include "cocos2d.h"

class VisibleRectUtils
{
public:
    static cocos2d::Rect visibleRect();
    static cocos2d::Vec2 left();
    static cocos2d::Vec2 right();
    static cocos2d::Vec2 top();
    static cocos2d::Vec2 bottom();
    static cocos2d::Vec2 center();
    static cocos2d::Vec2 leftTop();
    static cocos2d::Vec2 rightTop();
    static cocos2d::Vec2 leftBottom();
    static cocos2d::Vec2 rightBottom();
private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};

#endif /* VisibleRectUtils_hpp */
