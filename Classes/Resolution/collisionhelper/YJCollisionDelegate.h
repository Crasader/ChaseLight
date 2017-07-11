//
//  YJCollisionDelegate.h
//  4399zmxyx
//
//  Created by 06 4399 on 12-9-11.
//  Copyright (c) 2012年 4399 ios. All rights reserved.
//

#ifndef _YJCollisionDelegate_h
#define _YJCollisionDelegate_h

#include "YJCollisionMacros.h"

NS_YJCOLLISON_BEGIN

class CollisionObject;

class CollisionDelegate{
public:
    //-- Object collision delegate methods
    //** optional
    // Return true if a collision occured between the object and any other one
    virtual bool testCollide(CollisionObject* object){return false;};
    // Handle the collision between the target and its colliding objects
    virtual void handleCollision(CollisionObject* object){};
};

NS_YJCOLLISON_END

#endif
