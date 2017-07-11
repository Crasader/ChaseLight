//
//  YJCollisionObject.cpp
//  4399suitang
//
//  Created by 06 4399 on 12-7-25.
//  Copyright (c) 2012年 4399 ios. All rights reserved.
//

#include "YJCollisionObject.h"
#include "YJCollisionDelegate.h"
#include "YJConstant.h"

#include <stdlib.h>

NS_YJCOLLISON_BEGIN

CollisionObject::CollisionObject():
m_pass(CLDP_NONE),
m_collisionEnabled(true),
m_aabb_updated(false),
m_obb_updated(false),
m_collision_delegate(NULL),
m_groupIndex(COLLISION_UNGROUPED),
m_groupIndexOfTarget(COLLISION_UNGROUPED)
{
    
}

CollisionObject::CollisionObject(const CollisionObject& other){
    m_pass = other.m_pass;
    m_local_bb = other.m_local_bb;
    m_aabb = other.m_aabb;
    m_obb = other.m_obb;
    m_aabb_updated = false;
    m_obb_updated = false;
    m_collision_delegate = other.m_collision_delegate;
    m_collisionEnabled = other.m_collisionEnabled;
    m_groupIndex = other.m_groupIndex;
    m_groupIndexOfTarget = other.m_groupIndexOfTarget;
}

void CollisionObject::updateAABB(float x1, float y1, float x2, float y2){
    m_aabb.update(x1, y1, x2, y2);
    m_aabb_updated = true;
}
void CollisionObject::updateOBB(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    m_obb.update(x1, y1, x2, y2, x3, y3, x4, y4);
    m_obb_updated = true;
}

void CollisionObject::updateAABB(const AABB& other){
    m_aabb = other;
    m_aabb_updated = true;
}
void CollisionObject::updateOBB(const OBB& other){
    m_obb = other;
    m_obb_updated = true;
}

bool CollisionObject::collideWith(CollisionObject& other, bool ignoreCollisionGroup){
    if (this == &other) {
        return false;
    }
    
    if (!m_collisionEnabled || m_pass == CLDP_NONE) {
        return false;
    }
    
    
    if(
       !ignoreCollisionGroup &&
       getGroupIndex()!=COLLISION_UNGROUPED &&
       other.getGroupIndex()!=COLLISION_UNGROUPED
      ){
        if (getGroupIndex()!=other.getGroupIndex()) {
            return false;
        }
        else if (getGroupIndex()<0) {
            return false;
        }
    }
    
    bool pass_rslt = true;
    
    if (m_pass & CLDP_AABB) {
        if (needUpdateAABB()) {
            updateAABB();
        }
        if (other.needUpdateAABB()) {
            other.updateAABB();
        }
        
        pass_rslt = m_aabb.isZeroBB()?false:m_aabb.instersectWith(other.m_aabb);
    }
    
    if (pass_rslt && (m_pass & CLDP_OBB)) {
        if (needUpdateOBB()) {
            updateOBB();
        }
        if (other.needUpdateOBB()) {
            other.updateOBB();
        }
        pass_rslt = m_obb.isZeroBB()?false:m_obb.instersectWith(other.m_obb);
    }
    
    return pass_rslt;
}

bool CollisionObject::collideWithAny(){
    if (m_collisionEnabled && NULL!=m_collision_delegate) {
        return m_collision_delegate->testCollide(this);
    }
    return false;
}

void CollisionObject::handleCollision(){
    if (m_collisionEnabled && NULL!=m_collision_delegate /* && collideWithAny()*/) {
        m_collision_delegate->handleCollision(this);
    }
}

void CollisionObject::hasCollidedWith(CollisionObject& other){
    //** Override this method to handle the result of the collision
}

bool CollisionObject::detectCollision(CollisionObject& objA, CollisionObject& objB){
    return objA.collideWith(objB);
}

NS_YJCOLLISON_END