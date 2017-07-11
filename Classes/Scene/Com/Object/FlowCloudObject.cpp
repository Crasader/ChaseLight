//
//  FlowCloudObject.cpp
//  RollingBall
//
//  Created by Reyn-Mac on 2017/6/24.
//
//

#include "FlowCloudObject.hpp"
#define PIXELS_PER_SECOND (100)

bool FlowCloudObject::init()
{
    if(!Sprite::init()) {
        return false;
    }
    
    initWithFile("noise.png");
    cocos2d::Texture2D::TexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    getTexture()->setTexParameters(params);
    setTextureRect(VisibleRectUtils::visibleRect());
    
    return true;
}

void FlowCloudObject::onEnter() {
    Sprite::onEnter();
    scheduleUpdate();
}

void FlowCloudObject::onExit() {
    unscheduleUpdate();
    Sprite::onExit();
}

void FlowCloudObject::update(float dt) {
    static float offset = 0;
    offset += PIXELS_PER_SECOND * dt;
    Size textureSize = getTextureRect().size;
    setTextureRect(Rect(Vec2(offset, 0), textureSize));
    if(offset >= textureSize.width) {
        offset = 0;
    }
}
