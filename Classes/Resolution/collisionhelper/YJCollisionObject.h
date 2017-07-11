//
//  YJCollisionObject.h
//  4399suitang
//
//  Created by 06 4399 on 12-7-25.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _YJCollisionObject_h
#define _YJCollisionObject_h

#include "YJAABB.h"
#include "YJOBB.h"

#include "CCPlatformMacros.h"
#include <vector>

NS_YJCOLLISON_BEGIN

class CollisionDelegate;

class CollisionObject{
public:
    CollisionObject();
    CollisionObject(const CollisionObject& other);
    enum COLLIDE_PASS{
        CLDP_NONE = 0,
        CLDP_AABB = 0x1,
        CLDP_OBB = 0x2,
        
        /* If the pass is (CLDP_AABB|CLDP_OBB),
         * then the two objects will do AABB detection first,
         * and if the AABB result is true then do OBB detection.
         */
    };
    void    setCollidePass(int pass){m_pass = pass;}
    int     getCollidePass()const{return m_pass;}
    
    // Check if a collision event occurs between this and the other
    virtual bool collideWith(CollisionObject& other, bool ignoreCollisionGroup=false);
    
    // Let collision delegate to check if any collision occured between this and any others
    virtual bool collideWithAny();
    
    // Let collision delegate raise collision event between this and others
    virtual void handleCollision();
    
    // Collision delegate should call this method while a collision event has been raise between this and another
    virtual void hasCollidedWith(CollisionObject& other);
    
    virtual void updateAABB(){m_aabb_updated = true;}
    virtual void updateAABB(float x1, float y1, float x2, float y2);
    virtual void updateAABB(const AABB& other);
    const AABB& getAABB(){return m_aabb;}
    
    virtual void updateOBB(){m_obb_updated = true;}
    virtual void updateOBB(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    virtual void updateOBB(const OBB& other);
    const OBB& getOBB(){return m_obb;}
    
    
    virtual void resetAABBUpdate(){m_aabb_updated = false;}
    virtual void resetOBBUpdate(){m_obb_updated = false;}
    virtual void resetUpdate(){resetAABBUpdate();resetOBBUpdate();}
    
    virtual bool needUpdateAABB(){return !m_aabb_updated;}
    virtual bool needUpdateOBB(){return !m_obb_updated;}
    
    virtual void setLocalBB(const AABB& localBB){m_local_bb=localBB;}
    const AABB& localBB(){return m_local_bb;}
    
    virtual void setCollisionDelegate(CollisionDelegate* delegate){m_collision_delegate = delegate;}
    virtual CollisionDelegate* getCollisionDelegate(){return m_collision_delegate;}
    
    // Enable/disable collision
    //** The default value is true
    void setCollisionEnabled(bool enabled){m_collisionEnabled = enabled;}
    inline bool isCollisionEnabled(){return m_collisionEnabled;}
    
public:
    
    // Use the pass method of objA to detect the collision between objA and objB
    static bool detectCollision(CollisionObject& objA, CollisionObject& objB);
    
    CC_SYNTHESIZE(int, m_groupIndex, GroupIndex);
    CC_SYNTHESIZE(int, m_groupIndexOfTarget, GroupIndexOfTarget);
//    std::vector<int> m_groupIndexesOfTarget;
    
protected:
    int     m_pass;
    bool    m_collisionEnabled;
    
    AABB    m_aabb;
    OBB     m_obb;
    
    AABB    m_local_bb;
    
    bool m_aabb_updated;
    bool m_obb_updated;
    
    CollisionDelegate* m_collision_delegate;    //** Weak reference
};

NS_YJCOLLISON_END

#endif
