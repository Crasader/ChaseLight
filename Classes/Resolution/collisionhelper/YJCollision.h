//
//  YJCollision.h
//  4399suitang
//
//  Created by 06 4399 on 12-7-25.
//  Copyright (c) 2012年 4399. All rights reserved.
//

#ifndef _YJCollision_h
#define _YJCollision_h

#include "YJCollisionObject.h"

namespace cocos2d {
    class CCRect;
    class CCAffineTransform;
}

//-- Helper methods
extern void CCRectApplyAffineTransformToAABB(const cocos2d::CCRect& rect, YJCollision::AABB& aabb, const cocos2d::CCAffineTransform& anAffineTransform);

extern void CCRectApplyAffineTransformToOBB(const cocos2d::CCRect& rect, YJCollision::OBB& obb, const cocos2d::CCAffineTransform& anAffineTransform);

extern YJCollision::AABB CCRectToAABB(const cocos2d::CCRect& rect);

extern YJCollision::OBB  CCRectToOBB(const cocos2d::CCRect& rect);

extern void LocalBBApplyAffineTransformToAABB(const YJCollision::AABB& localBB, YJCollision::AABB& aabb, const cocos2d::CCAffineTransform& anAffineTransform);

extern void LocalBBApplyAffineTransformToOBB(const YJCollision::AABB& localBB, YJCollision::OBB& obb, const cocos2d::CCAffineTransform& anAffineTransform);

#endif
