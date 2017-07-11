//
//  YJNativeHelper.h
//  4399zmxyx
//
//  Created by mimicry on 5/27/13.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//

#ifndef ___399zmxyx__YJNativeHelper__
#define ___399zmxyx__YJNativeHelper__

#include <string>

#define YJJNI_EVENT_START_TO_COPY_FILE \
"YJJNI_EVENT_START_TO_COPY_FILE"

#define YJJNI_EVENT_COPY_FILE_SUCCESSFUL \
"YJJNI_EVENT_COPY_FILE_SUCCESSFUL"

#define YJJNI_EVENT_COPY_FILE_FAILED \
"YJJNI_EVENT_COPY_FILE_FAILED"

#define YJJNI_EVENT_COPY_ASSESTS_FINISHED \
"YJJNI_EVENT_COPY_ASSESTS_FINISHED"

#define YJJNI_COPY_ASSESTS_RESULT_OK \
"YJJNI_COPY_ASSESTS_RESULT_OK"

#define YJJNI_COPY_ASSESTS_RESULT_FAILED \
"YJJNI_COPY_ASSESTS_RESULT_FAILED"

extern void yjJNICopyAssetsToSdCard();

extern const std::string& yjJNIGetLastErrorMessage();

extern const std::string& yjJNIGetExternalAssetPath();

extern const std::string& yjJNIGetExternalUpdatePath();

extern void yjJNIOpenUrl(const char* pUrlCString);

extern void yjJNICheckDownloadedApk(const char* pApkFilePath, int newApkVersionCode);

extern bool yjJNIInstallApk(const char* pApkFilePath, int apkVersionCode);

extern bool yjJNIVerifyApk(const char* pApkFilePath, int apkVersionCode);

extern bool yjJNIIsNetStatus2G();

extern bool yjJNIIsNetStatus3G();

extern bool yjJNIIsNetStatusWifi();

extern bool yjJNIIsTabletDevice();

extern void yjJNIOpenWebView(const char* url, const char* tag);

extern void yjJNIOpenStrategyWebView(const char* url, const char* tag);

extern std::string yjJNIGetApkSignatureBytesArray();

extern bool yjJNIIsTabletDevice();

#endif /* defined(___399zmxyx__YJNativeHelper__) */
