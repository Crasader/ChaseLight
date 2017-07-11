//
//  YJNetworkHelper.cpp
//  4399zmxyx
//
//  Created by longyan on 13-7-18.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#include "YJNetworkHelper.h"
#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "YJNativeHelper.h"
void yjOpenURL(const char* url) {
	yjJNIOpenUrl(url);
}

bool yjIsNetStatus2G() {
    return yjJNIIsNetStatus2G();
}

bool yjIsNetStatus3G() {
    return yjJNIIsNetStatus3G();
}

bool yjIsNetStatusWifi() {
    return yjJNIIsNetStatusWifi();
}

void yjViewMoreGame() {
	yjJNIViewMoreGame();
}

#elif (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
void yjOpenURL(const char* url) {
    //** Not implement yet
}

bool yjIsNetStatus2G() {
    //** Not implement yet
    return false;
}

bool yjIsNetStatus3G() {
    //** Not implement yet
    return false;
}

bool yjIsNetStatusWifi() {
    //** Not implement yet
    return true;
}

void yjViewMoreGame() {
    //** Not implement yet
}
#endif
