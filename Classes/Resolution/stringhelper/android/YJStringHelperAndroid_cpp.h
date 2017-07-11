//
//  YJStringHelperAndroid_cpp.h
//  4399zmxyx
//
//  Created by mimicry on 7/24/13.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//

#ifndef _399zmxyx_YJStringHelperAndroid_cpp_h
#define _399zmxyx_YJStringHelperAndroid_cpp_h

#include "jni/JniHelper.h"
#include <android/log.h>

USING_NS_CC;

#define  LOG_TAG    "YJStringHelperAndroid_cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  COCOS2DX_BITMAP_CLASS_NAME "org/cocos2dx/lib/Cocos2dxBitmap"
#define  COCOS2DX_TEXT_IMG_SIZE_CLASS_NAME "org/cocos2dx/lib/Cocos2dxBitmap$TextImgSize"

using namespace cocos2d;

extern "C" {
    
    void yjCaculateLabelSize_(const char * pText,
                              const char * pFontName,
                              int nFontSize,
                              unsigned int nConstrainWidth,
                              unsigned int nConstrainHeight,
                              CCTextAlignment alignment,
                              CCVerticalTextAlignment vertAlignment,
                              unsigned int* pDimensionWidthOut,
                              unsigned int* pDimensionHeightOut)
    {
        JniMethodInfo methodInfo;
        if (! JniHelper::getStaticMethodInfo(methodInfo, COCOS2DX_BITMAP_CLASS_NAME, "getTextBitmapSize",
                                             "(Ljava/lang/String;Ljava/lang/String;IIII)Lorg/cocos2dx/lib/Cocos2dxBitmap$TextImgSize;"))
        {
            LOGD("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        
        CCImage::ETextAlign eAlign;
        if (kCCVerticalTextAlignmentTop == vertAlignment)
        {
            eAlign = (kCCTextAlignmentCenter == alignment) ? CCImage::kAlignTop
            : (kCCTextAlignmentLeft == alignment) ? CCImage::kAlignTopLeft : CCImage::kAlignTopRight;
        }
        else if (kCCVerticalTextAlignmentCenter == vertAlignment)
        {
            eAlign = (kCCTextAlignmentCenter == alignment) ? CCImage::kAlignCenter
            : (kCCTextAlignmentLeft == alignment) ? CCImage::kAlignLeft : CCImage::kAlignRight;
        }
        else if (kCCVerticalTextAlignmentBottom == vertAlignment)
        {
            eAlign = (kCCTextAlignmentCenter == alignment) ? CCImage::kAlignBottom
            : (kCCTextAlignmentLeft == alignment) ? CCImage::kAlignBottomLeft : CCImage::kAlignBottomRight;
        }
        else
        {
            
            CCAssert(false, "Not supported alignment format!");
            LOGD("Not supported alignment format!");
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return;
        }

        // Do a full lookup for the font path using CCFileUtils in case the given font name is a relative path to a font file asset,
        // or the path has been mapped to a different location in the app package:
        std::string fullPathOrFontName = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFontName);
        
        // If the path name returned includes the 'assets' dir then that needs to be removed, because the android.content.Context
        // requires this portion of the path to be omitted for assets inside the app package.
        if (fullPathOrFontName.find("assets/") == 0)
        {
            fullPathOrFontName = fullPathOrFontName.substr(strlen("assets/"));	// Chop out the 'assets/' portion of the path.
        }
        
//        JNIEnv* env = 0;
//        if (JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK || ! env) {
//            return 0;
//        }
        JNIEnv* env = methodInfo.env;
        
        jclass clazz = env->FindClass(COCOS2DX_TEXT_IMG_SIZE_CLASS_NAME); 
        if (!clazz)
        {
            LOGD("Failed to find class of %s", COCOS2DX_TEXT_IMG_SIZE_CLASS_NAME);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return;
        }
        
        jfieldID field_w = env->GetFieldID(clazz, "w", "I"); //** no need to DeleteLocalRef jfieldID and jmethodID 
        if (!field_w) {
            LOGD("Failed to find filed w of class %s", COCOS2DX_TEXT_IMG_SIZE_CLASS_NAME);
            methodInfo.env->DeleteLocalRef(clazz);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return;
        }
        
        jfieldID field_h = env->GetFieldID(clazz, "h", "I");
        if (!field_h) {
            LOGD("Failed to find filed h of class %s", COCOS2DX_TEXT_IMG_SIZE_CLASS_NAME);
            methodInfo.env->DeleteLocalRef(clazz);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return;
        }
        
        jstring jstrText = methodInfo.env->NewStringUTF(pText);
        jstring jstrFont = methodInfo.env->NewStringUTF(fullPathOrFontName.c_str());
        
        jobject jRetObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, jstrText,
                                             jstrFont, (int)nFontSize, eAlign, nConstrainWidth, nConstrainHeight);
        
        int img_w = env->GetIntField(jRetObj, field_w);
        int img_h = env->GetIntField(jRetObj, field_h);
        
        methodInfo.env->DeleteLocalRef(jRetObj);
        methodInfo.env->DeleteLocalRef(jstrText);
        methodInfo.env->DeleteLocalRef(jstrFont);
        methodInfo.env->DeleteLocalRef(clazz);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
        LOGD("Text image size:(%d, %d)", img_w, img_h);
        
        if (NULL != pDimensionWidthOut) {
            *pDimensionWidthOut = img_w;
        }
        
        if (NULL != pDimensionHeightOut) {
            *pDimensionHeightOut = img_h;
        }
    }
    
}


#endif
