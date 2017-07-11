//
//  YJNativeHelper.cpp
//  4399zmxyx
//
//  Created by mimicry on 5/27/13.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//

#include "YJNativeHelper.h"
#include "YJConstant.h"
#include "YJCryptor.h"
#include "YJDebugMacro.h"
#include "YJEventConstant.h"
#include "YJDataManager.h"
#include "YJObjectData.h"
#include "YJGameGuardHelper.h"
#include "cocos2d.h"
#include "JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "YJNativeHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  HELPER_CLASS_NAME "org/yjmobile/lib/YJMobileJNIHelper"

using namespace cocos2d;

static std::string g_sLastErrorMsg;
static std::string g_sExternalAssetPath;
static std::string g_sExternalUpdatePath;

extern "C" {
//    JNIEXPORT jstring JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeGetDK(JNIEnv* env) {
//        jstring ret;
//        ret = env->NewStringUTF(SECRET_KEY);
//        return ret;
//    }
    
//    JNIEXPORT jstring JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeDesEncrypt(JNIEnv* env, jobject thiz, jstring rawData) {
//        const char* rawdata_cstr = env->GetStringUTFChars(rawData, NULL);
//        std::string rawdata_str(rawdata_cstr);
//        env->ReleaseStringUTFChars(rawData, rawdata_cstr);
//        unsigned long buffer_size = 0;
//        unsigned char* buffer = NULL;
//        yjDesEncrypt((unsigned char const*)SECRET_KEY, (unsigned char const*)rawdata_str.c_str(), rawdata_str.length(), &buffer, &buffer_size);
//        jstring ret;
//        ret = env->NewStringUTF((char*)buffer);
//        delete [] buffer;
//        return ret;
//    }
    
    JNIEXPORT jstring JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeDesDecrypt(JNIEnv* env, jobject thiz, jstring encryptedData) {
        const char* encrypteddata_cstr = env->GetStringUTFChars(encryptedData, NULL);
        std::string encrypteddata_str(encrypteddata_cstr);
        env->ReleaseStringUTFChars(encryptedData, encrypteddata_cstr);
        unsigned char* buffer = NULL;
        unsigned long buffer_size = 0;
        yjDesDecrypt((unsigned char const*)SECRET_KEY, (unsigned char*)encrypteddata_str.c_str(), encrypteddata_str.length(), &buffer, &buffer_size);
        jstring ret;
        ret = env->NewStringUTF((char*)buffer);
        delete [] buffer;
        return ret;
    }
    
    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeStartToCopyFile(JNIEnv* env, jobject thiz, jstring fileName) {
        const char* fileName_cstr = env->GetStringUTFChars(fileName, NULL);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(YJJNI_EVENT_START_TO_COPY_FILE, CCString::create(fileName_cstr));
        env->ReleaseStringUTFChars(fileName, fileName_cstr);
    }
    
    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeCopyFileSuccessful(JNIEnv* env, jobject thiz, jstring fileName, int copyedFilesCount, int totalFilesToCopyCount) {
        const char* fileName_cstr = env->GetStringUTFChars(fileName, NULL);
        CCArray* paramArr = CCArray::create();
        paramArr->addObject(CCString::create(fileName_cstr));
        paramArr->addObject(CCInteger::create(copyedFilesCount));
        paramArr->addObject(CCInteger::create(totalFilesToCopyCount));
        CCNotificationCenter::sharedNotificationCenter()->postNotification(YJJNI_EVENT_COPY_FILE_SUCCESSFUL, paramArr);
        env->ReleaseStringUTFChars(fileName, fileName_cstr);
    }
    
    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeCopyFileFailed(JNIEnv* env, jobject thiz, jstring fileName, jstring errorMsg) {
        const char* errorMsg_cstr = env->GetStringUTFChars(errorMsg, NULL);
        g_sLastErrorMsg = errorMsg_cstr;
        env->ReleaseStringUTFChars(errorMsg, errorMsg_cstr);

        const char* fileName_cstr = env->GetStringUTFChars(fileName, NULL);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(YJJNI_EVENT_COPY_FILE_FAILED, CCString::create(fileName_cstr));
        env->ReleaseStringUTFChars(fileName, fileName_cstr);
        
    }
    
    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeCopyAssetsFinished(JNIEnv* env, jobject thiz, jstring fileName, jboolean bIsCopyProcessOK) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(YJJNI_EVENT_COPY_ASSESTS_FINISHED, CCString::create((bIsCopyProcessOK!=JNI_FALSE)?YJJNI_COPY_ASSESTS_RESULT_OK:YJJNI_COPY_ASSESTS_RESULT_FAILED));
    }
    
    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeSetExternalAssetPath(JNIEnv*  env, jobject thiz, jstring externalAssetPath) {
        const char* externalAssetPathChars = env->GetStringUTFChars(externalAssetPath, NULL);
        g_sExternalAssetPath = externalAssetPathChars;
        env->ReleaseStringUTFChars(externalAssetPath, externalAssetPathChars);
    }

    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeSetExternalUpdatePath(JNIEnv*  env, jobject thiz, jstring externalUpdatePath) {
        const char* externalUpdatePathChars = env->GetStringUTFChars(externalUpdatePath, NULL);
        g_sExternalUpdatePath = externalUpdatePathChars;
        env->ReleaseStringUTFChars(externalUpdatePath, externalUpdatePathChars);
    }
    
    JNIEXPORT jboolean JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_native4399HCEnabled(JNIEnv* env, jobject thiz) {
    	jboolean jb_ret = JNI_TRUE;
#ifdef DEBUG
    	if (!DEBUG_GAME_CHEATER_DETECTIVE_ON())
    		jb_ret = JNI_FALSE;
#endif
        return jb_ret;
    }

    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeOnWebViewClosed(JNIEnv* env, jobject thiz, jstring webviewTag) {
        const char* webviewTagChars = env->GetStringUTFChars(webviewTag, NULL);
        std::string webviewTagStr = webviewTagChars;
        env->ReleaseStringUTFChars(webviewTag, webviewTagChars);
        CCNotificationCenter::sharedNotificationCenter()->postNotification(YJ_EVENT_WEBVIEW_CLOSED, CCString::create(webviewTagStr));
    }

    //** Get the game cheater process name array
    JNIEXPORT jobjectArray JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeGetHackerProcessInfoArray(JNIEnv* env, jobject thiz) {
    	DATA_LIST data_list = YJDataManager::sharedManager()->queryDataListByType(DT_GAME_GUARD);
    	jobjectArray ret = 0;
    	int length = data_list.size();
    	jclass objectClass = (env)->FindClass("org/yjmobile/lib/YJGameGuardInfo");
    	ret = (env)->NewObjectArray(length,objectClass,0);
    	jfieldID str_process_name = (env)->GetFieldID(objectClass,"process_name","Ljava/lang/String;");
    	jfieldID i_id = (env)->GetFieldID(objectClass,"id","I");
    	jfieldID i_type = (env)->GetFieldID(objectClass,"type","I");
    	jfieldID i_compare_strategy = (env)->GetFieldID(objectClass,"compare_strategy","I");
    	jmethodID game_guard_constructor = env->GetMethodID(objectClass , "<init>","()V");
    	int idx = 0;
    	for (DATA_LIST::iterator it = data_list.begin(); it != data_list.end();
			++it, ++idx) {
    		const YJGameGuardData* game_guard_data = dynamic_cast<const YJGameGuardData*>(*it);

        	jobject game_guard_obj = (env)->NewObject(objectClass,game_guard_constructor);
    		(env)->SetIntField(game_guard_obj,i_id,game_guard_data->id.raw());
    		(env)->SetIntField(game_guard_obj,i_type,game_guard_data->type);
    		(env)->SetIntField(game_guard_obj,i_compare_strategy,game_guard_data->compare_strategy);
    		jstring process_name = (env)->NewStringUTF(game_guard_data->process_name);
    		(env)->SetObjectField(game_guard_obj,str_process_name,process_name);
    		(env)->DeleteLocalRef(process_name);

    		(env)->SetObjectArrayElement(ret, idx, game_guard_obj);
        	(env)->DeleteLocalRef(game_guard_obj);
    	}
    	(env)->DeleteLocalRef(objectClass);
    	return ret;
    }

    JNIEXPORT jboolean JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeNeedToReloadHackerProcessInfoArray(JNIEnv* env, jobject thiz) {
    	return yjNeedToReloadHackerInfos();
    }

    JNIEXPORT void JNICALL Java_org_yjmobile_lib_YJMobileJNIHelper_nativeSetNeedToReloadHackerProcessInfoArray(JNIEnv* env, jobject thiz,jboolean needToReload) {
    	yjSetNeedToReloadHackerInfos(needToReload);
    }

    void yjCopyAssetsToSdCard_() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "copyAssets", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void yjJNIOpenUrl_(const char* pUrlCString) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "openUrl", "(Ljava/lang/String;)V")) {
            jstring jstrUrl = t.env->NewStringUTF(pUrlCString);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jstrUrl);
            t.env->DeleteLocalRef(jstrUrl);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void yjJNICheckDownloadedApk_(const char* pApkFilePath, int newApkVersionCode) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "onCreateNewApk", "(Ljava/lang/String;I)Z")) {
            jstring jstrApkFilePath = t.env->NewStringUTF(pApkFilePath);
            t.env->CallStaticBooleanMethod(t.classID, t.methodID, jstrApkFilePath, newApkVersionCode);
            t.env->DeleteLocalRef(jstrApkFilePath);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    bool yjJNIInstallApk_(const char* pApkFilePath, int apkVersionCode) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "installApk", "(Ljava/lang/String;I)Z")) {
            jstring jstrApkFilePath = t.env->NewStringUTF(pApkFilePath);
            jboolean jb_ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, jstrApkFilePath, apkVersionCode);
            t.env->DeleteLocalRef(jstrApkFilePath);
            t.env->DeleteLocalRef(t.classID);
            return (jb_ret!=JNI_FALSE);
        }
        return false;
    }
    
    bool yjJNIVerifyApk_(const char* pApkFilePath, int apkVersionCode) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "verifyApk", "(Ljava/lang/String;I)Z")) {
            jstring jstrApkFilePath = t.env->NewStringUTF(pApkFilePath);
            jboolean jb_ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, jstrApkFilePath, apkVersionCode);
            t.env->DeleteLocalRef(jstrApkFilePath);
            t.env->DeleteLocalRef(t.classID);
            return (jb_ret!=JNI_FALSE);
        }
        return false;
    }
    
    bool yjJNIIsNetStatus2G_() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "isNetStatus2G", "()Z")) {
            jboolean jb_ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            return (jb_ret!=JNI_FALSE);
        }
        return false;
    }
    
    bool yjJNIIsNetStatus3G_() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "isNetStatus3G", "()Z")) {
            jboolean jb_ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            return (jb_ret!=JNI_FALSE);
        }
        return false;
    }
    
    bool yjJNIIsNetStatusWifi_() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "isNetStatusWifi", "()Z")) {
            jboolean jb_ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            return (jb_ret!=JNI_FALSE);
        }
        return false;
    }

    bool yjJNIIsTabletDevice_() {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "isTabletDevice", "()Z")) {
            jboolean jb_ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
            return (jb_ret!=JNI_FALSE);
        }
        return false;
    }

    void yjJNIOpenWebView_(const char* url, const char* tag) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "openWebView", "(Ljava/lang/String;Ljava/lang/String;ZZ)V")) {
            jstring jstrURL = t.env->NewStringUTF(url);
            jstring jstrTag = t.env->NewStringUTF(tag);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jstrURL, jstrTag, true, true);
            t.env->DeleteLocalRef(jstrURL);
            t.env->DeleteLocalRef(jstrTag);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void yjJNIOpenStrategyWebView_(const char* url, const char* tag) {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, HELPER_CLASS_NAME, "openWebView", "(Ljava/lang/String;Ljava/lang/String;ZZ)V")) {
            jstring jstrURL = t.env->NewStringUTF(url);
            jstring jstrTag = t.env->NewStringUTF(tag);
            t.env->CallStaticVoidMethod(t.classID, t.methodID, jstrURL, jstrTag, false, true);
            t.env->DeleteLocalRef(jstrURL);
            t.env->DeleteLocalRef(jstrTag);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    std::string yjJNIGetApkSignatureBytesArray_(){
        JniMethodInfo t;
        //** Get Context in YJMobileJNIHelper
        if(JniHelper::getStaticMethodInfo(t,HELPER_CLASS_NAME,"getContext","()Landroid/content/Context;")){
        	jobject context = t.env->CallStaticObjectMethod(t.classID,t.methodID);
        	//** Get PackageManager
        	jclass class_context = t.env->GetObjectClass(context);
        	jmethodID methodID_getPackageManager = t.env->GetMethodID(class_context,"getPackageManager","()Landroid/content/pm/PackageManager;");
        	t.env->DeleteLocalRef(class_context);
        	jobject package_manager = t.env->CallObjectMethod(context,methodID_getPackageManager);
        	t.env->DeleteLocalRef(context);
        	//** Get Package info
        	jclass class_package_manager = t.env->GetObjectClass(package_manager);
        	jmethodID methodID_getPackageInfo = t.env->GetMethodID(class_package_manager,"getPackageInfo","(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
        	t.env->DeleteLocalRef(class_package_manager);
        	//-- PackageManager: public static final int GET_SIGNATURES = 64;
        	jstring jstrPackageName = t.env->NewStringUTF("org.yjmobile.zmxy");
        	jobject package_info = t.env->CallObjectMethod(package_manager,methodID_getPackageInfo,jstrPackageName,64);
        	t.env->DeleteLocalRef(package_manager);//<< Delete package_manager
        	t.env->DeleteLocalRef(jstrPackageName);//<< Delete jstrPackageName

        	//** Get Package signatures
        	jclass class_package_info = t.env->GetObjectClass(package_info);
        	jfieldID fieldID_signatures = t.env->GetFieldID(class_package_info,"signatures","[Landroid/content/pm/Signature;");
        	t.env->DeleteLocalRef(class_package_info);//<< Delete class_package_info
        	jobjectArray signatures = (jobjectArray)t.env->GetObjectField(package_info,fieldID_signatures);
        	t.env->DeleteLocalRef(package_info);//<< Delete package_info
        	jobject signature = t.env->GetObjectArrayElement(signatures,0);
        	t.env->DeleteLocalRef(signatures);//<< Delete sinautures

        	//** Get Package signatures bytes
        	jclass class_signature = t.env->GetObjectClass(signature);
        	jmethodID methodID_toByteArray = t.env->GetMethodID(class_signature, "toByteArray", "()[B");
        	t.env->DeleteLocalRef(class_signature);//<< Delete class_signature
        	jbyteArray jbyteArray_signature = (jbyteArray)t.env->CallObjectMethod(signature,methodID_toByteArray);
        	t.env->DeleteLocalRef(signature);//<< Delete signature
        	jbyte* signature_buff = t.env->GetByteArrayElements(jbyteArray_signature, NULL);
        	int signature_buff_size = t.env->GetArrayLength(jbyteArray_signature);
        	std::string str_signature((const char*)signature_buff, signature_buff_size);
        	t.env->ReleaseByteArrayElements(jbyteArray_signature, signature_buff, JNI_ABORT);//<< Delete signature_buff
        	t.env->DeleteLocalRef(jbyteArray_signature);//<< Delete jbyteArray_signature
        	t.env->DeleteLocalRef(t.classID);
        	return str_signature;
        }
        return "";
    }
}

const std::string& yjJNIGetLastErrorMessage() {
    return g_sLastErrorMsg;
}

const std::string& yjJNIGetExternalAssetPath() {
    return g_sExternalAssetPath;
}

const std::string& yjJNIGetExternalUpdatePath() {
    if (g_sExternalUpdatePath.empty())
    {
        static std::string internal_update_path;
        internal_update_path = CCFileUtils::sharedFileUtils()->getWritablePath();
        internal_update_path += "update/";
        return internal_update_path;
    }
    return g_sExternalUpdatePath;
}

void yjJNICopyAssetsToSdCard() {
    yjCopyAssetsToSdCard_();
}

void yjJNIOpenUrl(const char* pUrlCString) {
	yjJNIOpenUrl_(pUrlCString);
}

void yjJNICheckDownloadedApk(const char* pApkFilePath, int newApkVersionCode) {
	yjJNICheckDownloadedApk_(pApkFilePath, newApkVersionCode);
}

bool yjJNIInstallApk(const char* pApkFilePath, int apkVersionCode) {
	return yjJNIInstallApk_(pApkFilePath, apkVersionCode);
}

bool yjJNIVerifyApk(const char* pApkFilePath, int apkVersionCode) {
	return yjJNIVerifyApk_(pApkFilePath, apkVersionCode);
}

bool yjJNIIsNetStatus2G() {
    return yjJNIIsNetStatus2G_();
}

bool yjJNIIsNetStatus3G() {
    return yjJNIIsNetStatus3G_();
}

bool yjJNIIsNetStatusWifi() {
    return yjJNIIsNetStatusWifi_();
}

bool yjJNIIsTabletDevice() {
	return yjJNIIsTabletDevice_();
}

void yjJNIOpenWebView(const char* url, const char* tag) {
	return yjJNIOpenWebView_(url, tag);
}

void yjJNIOpenStrategyWebView(const char* url, const char* tag) {
	return yjJNIOpenStrategyWebView_(url, tag);
}

std::string yjJNIGetApkSignatureBytesArray(){
	return yjJNIGetApkSignatureBytesArray_();
}
