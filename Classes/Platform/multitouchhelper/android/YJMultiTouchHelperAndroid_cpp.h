//
//  YJUUIDAndroid_cpp.h
//  4399zmxyx
//
//  Created by mimicry on 5/18/13.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//
#include "JniHelper.h"
#include <android/log.h>
#include "ccMacros.h"

#define  LOG_TAG    "YJMultiTouchHelperAndroid_cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  ACTIVITY_CLASS_NAME "org/cocos2dx/lib/Cocos2dxActivity"

using namespace cocos2d;

extern "C" {
    
    void yjSetMultiTouchEnabled_(bool enabled) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, ACTIVITY_CLASS_NAME, "setMultiTouchEnabled", "(Z)V")) {
            jboolean jb_enabled = enabled?JNI_TRUE:JNI_FALSE;
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jb_enabled);
            t.env->DeleteLocalRef(t.classID);
            LOGD("%s multi-touch", enabled?"Enable":"Disable");
        }

    }
    
    bool yjIsMultiTouchEnabled_() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, ACTIVITY_CLASS_NAME, "isMultiTouchEnabled", "()Z")) {
            jboolean jb_enabled = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            LOGD("Multi-touch is ", (jb_enabled!=JNI_FALSE)?"enabled":"disabled");
            return (jb_enabled!=JNI_FALSE);
        }
        return false;
    }
}

void yjSetMultiTouchEnabled(bool enabled) {
    yjSetMultiTouchEnabled_(enabled);
}

bool yjIsMultiTouchEnabled() {
    return yjIsMultiTouchEnabled_();
}

