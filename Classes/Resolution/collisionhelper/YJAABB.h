//
//  YJAABB.h
//  4399suitang
//
//  Created by 06 4399 on 12-7-25.
//  Copyright (c) 2012年 4399 ios. All rights reserved.
//

#ifndef _YJAABB_h
#define _YJAABB_h

#include "YJCookedNum.h"
#include "YJCollisionMacros.h"

NS_YJCOLLISON_BEGIN

struct BoundPoint{
    BoundPoint():x(0),y(0){}
    YJCKFloat x;
    YJCKFloat y;
};

struct AABB{
    AABB(){
        update(0, 0, 0, 0);
    }
    
    AABB(float x1, float y1, float x2, float y2){
        update(x1, y1, x2, y2);
    }
    
    virtual void update(float x1, float y1, float x2, float y2){
        leftBottom.x = x1<x2?x1:x2;
        leftBottom.y = y1<y2?y1:y2;
        rightTop.x = x1>x2?x1:x2;
        rightTop.y = y1>y2?y1:y2;
    }
    
    virtual bool instersectWith(const AABB& other)const{
        return !(rightTop.x < other.leftBottom.x||
                 other.rightTop.x < leftBottom.x||
                 rightTop.y < other.leftBottom.y||
                 other.rightTop.y < leftBottom.y);  
    }
    
    AABB& operator= (const AABB& other){
        this->update(other.leftBottom.x.raw(), other.leftBottom.y.raw(), other.rightTop.x.raw(), other.rightTop.y.raw());
        return *this;
    }
    
    bool isZeroBB(){
        return (leftBottom.x==rightTop.x && leftBottom.y==rightTop.y);
    }
    

    BoundPoint leftBottom;
    BoundPoint rightTop;
};

NS_YJCOLLISON_END

#endif
