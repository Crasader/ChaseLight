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

#define  LOG_TAG    "YJUUIDAndroid_cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  OPENUDID_CLASS_NAME "net/openudid/android/OpenUDID"

using namespace cocos2d;

extern "C" {
    
    static std::string yjFetchUUIDString_(int* errorCode){
        // Get method information
        JniMethodInfo t;
//        if (JniHelper::getStaticMethodInfo(t, OPENUDID_CLASS_NAME, "getOpenUDIDInContext", "()Ljava/lang/String;")) {
//            jstring udid_jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
//            t.env->DeleteLocalRef(t.classID);
//            std::string udid_str = JniHelper::jstring2string(udid_jstr);
//            t.env->DeleteLocalRef(udid_jstr);
//            LOGD("UUID String:%s", udid_str.c_str());
//            return udid_str;
//        }
        
        //** Test udid with corp
        if (JniHelper::getStaticMethodInfo(t, OPENUDID_CLASS_NAME, "getCorpUDID", "(Ljava/lang/String;)Ljava/lang/String;")) {
            jstring corp_jstr = t.env->NewStringUTF("4399");
            jstring udid_jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, corp_jstr);
            t.env->DeleteLocalRef(t.classID);
            std::string udid_str = JniHelper::jstring2string(udid_jstr);
            t.env->DeleteLocalRef(corp_jstr);
            t.env->DeleteLocalRef(udid_jstr);
//            LOGD("Corp UUID(Md5) String:%s", udid_str.c_str());
            return udid_str;
        }
        
        CCAssert(false,"");
        LOGD("Unrecognized UUID String");
        return "unrecognized_udid";
    }
    
}

std::string yjFetchUUIDString(int* errorCode) {
    return yjFetchUUIDString_(errorCode);
}
