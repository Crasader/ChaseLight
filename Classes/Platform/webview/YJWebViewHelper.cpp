//
//  YJWebViewHelper.cpp
//  4399zmxyx
//
//  Created by Light0457 on 13-8-31.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//

#include "YJWebViewHelper.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "YJNativeHelper.h"
void yjOpenWebView(const char* url)
{
    yjJNIOpenWebView(url);
}

#elif (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
void yjOpenWebView(const char* url, const char* tag)
{
    /*
     * Not implemented yet
     */
}

void yjOpenStrategyWebView(const char* url, const char* tag)
{
    /*
     * Not implemented yet
     */
}

#endif
