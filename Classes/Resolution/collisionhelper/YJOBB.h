//
//  YJCCOBB.h
//  4399suitang
//
//  Created by 06 4399 on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _YJOBB_h
#define _YJOBB_h
#include "YJCollisionMacros.h"

NS_YJCOLLISON_BEGIN

struct OBB{
    OBB(){
        update(0, 0, 0, 0, 0, 0, 0, 0);
    }

    
    // Update the four vertexes counter clockwise from bottom left
    virtual void update(float x1, float y1,
                        float x2, float y2,
                        float x3, float y3,
                        float x4, float y4){
        leftBottom.x = x1;
        leftBottom.y = y1;
        rightBottom.x = x2;
        rightBottom.y = y2;
        rightTop.x = x3;
        rightTop.y = y3;
        leftTop.x = x4;
        leftTop.y = y4;
    }
    
    virtual bool instersectWith(const OBB& other)const{
        //< TODO
        return false;  
    }
    
    OBB& operator= (const OBB& other){
        this->update(other.leftBottom.x.raw(), other.leftBottom.y.raw(),
                     other.rightBottom.x.raw(), other.rightBottom.y.raw(),
                     other.rightTop.x.raw(), other.rightTop.y.raw(),
                     other.leftTop.x.raw(), other.leftTop.y.raw());
        return *this;
    }
    
    bool isZeroBB(){
        return (rightTop.x==leftBottom.x && rightTop.y==leftBottom.y);
    }
    
    BoundPoint leftBottom;
    BoundPoint rightBottom;
    BoundPoint rightTop;
    BoundPoint leftTop;
};

NS_YJCOLLISON_END

#endif
