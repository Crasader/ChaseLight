//
//  YJCollisionConstant.h
//  4399zmxyx
//
//  Created by mimicry on 9/10/12.
//  Copyright (c) 2012 4399 ios. All rights reserved.
//

#ifndef _YJCollisionConstant_h
#define _YJCollisionConstant_h

#include "YJCollision.h"
#include "CCGeometry.h"
#include "CCAffineTransform.h"

USING_NS_CC;
USING_NS_YJCOLLIOSN;

void CCRectApplyAffineTransformToAABB(const cocos2d::CCRect& rect, YJCollision::AABB& aabb, const cocos2d::CCAffineTransform& anAffineTransform){
    aabb = CCRectToAABB(CCRectApplyAffineTransform(rect, anAffineTransform));
}

void CCRectApplyAffineTransformToOBB(const CCRect& rect, OBB& obb, const CCAffineTransform& anAffineTransform){
    float top = rect.getMaxY();
    float left = rect.getMinX();
    float right = rect.getMaxX();
    float bottom = rect.getMinY();
    
    CCPoint topLeft = CCPointApplyAffineTransform(CCPointMake(left, top), anAffineTransform);
    CCPoint topRight = CCPointApplyAffineTransform(CCPointMake(right, top), anAffineTransform);
    CCPoint bottomLeft = CCPointApplyAffineTransform(CCPointMake(left, bottom), anAffineTransform);
    CCPoint bottomRight = CCPointApplyAffineTransform(CCPointMake(right, bottom), anAffineTransform);
    
    obb.update(bottomLeft.x, bottomLeft.y,
               bottomRight.x, bottomRight.y,
               topRight.x, topRight.y,
               topLeft.x, topLeft.y);
}

AABB CCRectToAABB(const CCRect& rect){
    AABB retAABB;
    retAABB.update(rect.getMinX(), rect.getMinY(), rect.getMaxX(), rect.getMaxY());
    return retAABB;
}

OBB CCRectToOBB(const CCRect& rect){
    float top = rect.getMaxY();
    float left = rect.getMinX();
    float right = rect.getMaxX();
    float bottom = rect.getMinY();

    OBB retOBB;
    retOBB.update(bottom, left, bottom, right, top, right, top, left);
    return retOBB;
}

void LocalBBApplyAffineTransformToAABB(const YJCollision::AABB& localBB, YJCollision::AABB& aabb, const CCAffineTransform& anAffineTransform){
    CCRect rect = CCRectMake(localBB.leftBottom.x.raw(), localBB.leftBottom.y.raw() , localBB.rightTop.x-localBB.leftBottom.x, localBB.rightTop.y-localBB.leftBottom.y);
    CCRectApplyAffineTransformToAABB(rect, aabb, anAffineTransform);
}

void LocalBBApplyAffineTransformToOBB(const YJCollision::AABB& localBB, YJCollision::OBB& obb, const CCAffineTransform& anAffineTransform){
    CCRect rect = CCRectMake(localBB.leftBottom.x.raw(), localBB.leftBottom.y.raw() , localBB.rightTop.x-localBB.leftBottom.x, localBB.rightTop.y-localBB.leftBottom.y);
    CCRectApplyAffineTransformToOBB(rect, obb, anAffineTransform);
}

#endif
