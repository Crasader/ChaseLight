//
//  YJMultiTouchHelper.cpp
//  4399zmxyx
//
//  Created by mimicry on 12/8/12.
//  Copyright (c) 2012 4399 ios. All rights reserved.
//

#include "YJMultiTouchHelper.h"
#include "CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/YJMultiTouchHelperAndroid_cpp.h"
#elif (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
void yjSetMultiTouchEnabled(bool enabled){}
bool yjIsMultiTouchEnabled(){return false;}
#endif