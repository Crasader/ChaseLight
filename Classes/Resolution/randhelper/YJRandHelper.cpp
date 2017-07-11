//
//  YJRandHelper.cpp
//  4399zmxyx
//
//  Created by Mimicry on 8/13/14.
//  Copyright (c) 2014 4399 ios. All rights reserved.
//

#include "YJRandHelper.h"
#include "YJDebugManager.h"
#include "YJGlobalManager.h"
#include <typeinfo>

static bool s_bIsExternalRandListEnabled = false;
static std::vector<unsigned> s_randList;
static unsigned s_randMin = 0;
static unsigned s_randMax = 0;
static unsigned s_randIdx = 0;

void yjSetExternalRandList(const std::vector<unsigned>& randList, unsigned randMin, unsigned randMax) {
    s_randList = randList;
    s_randMin = randMin;
    s_randMax = randMax;
    s_randIdx = 0; // reset index
}

void yjSetExternalRandListEnabled(bool enabled) {
    s_bIsExternalRandListEnabled = enabled;
}

static unsigned int yjRandFromExternalList() {
    if (s_randList.empty()) {
        return 0;
    }
    unsigned int ret = s_randList.at(s_randIdx);
    s_randIdx = (s_randIdx+1) % s_randList.size();
    ret = ret>s_randMax?s_randMax:ret;
    ret = ret<s_randMin?s_randMin:ret;
    return ret;
}

#ifdef DEBUG
static void yjLogRandResult(unsigned originRand, float resultRand, const void* invoker, bool outputInConsole);
#endif

float yjRandomInRangef(float rangeBegin, float rangeEnd, const void* invoker) {
    if (rangeEnd < rangeBegin) {
        return rangeBegin;
    }
    
    double random = 0.f;
    double rand_min = 0.f;
    double rand_max = RAND_MAX+1.f;
    if (s_bIsExternalRandListEnabled) {
        // Use external rand list
        rand_min = s_randMin;
        rand_max = s_randMax + 1.f;
        random = yjRandFromExternalList();
    }
    else {
        random = rand() - rand_min;
    }
    
    float ret = (random/rand_max)*(rangeEnd-rangeBegin)+rangeBegin;

#ifdef DEBUG
    yjLogRandResult(random, ret, invoker, true);
#endif

    return ret;
}

#ifdef DEBUG
#include "cocos2d.h"
#include "YJGameSceneProtocol.h"
static bool s_bIsLogRandResultOn = false;
static std::vector<unsigned> s_orignRandLog;
static std::vector<float> s_randResultLog;
static float s_lastRandResult = 0.f;

void yjSetLogRandResultOn(bool isOn) {
    s_bIsLogRandResultOn = isOn;
    s_orignRandLog.clear();
    s_randResultLog.clear();
}

static void yjLogRandResult(unsigned originRand, float resultRand, const void* invoker, bool outputInConsole) {
    if (!s_bIsLogRandResultOn) {
        return;
    }
    if (outputInConsole) {
        const cocos2d::CCObject* p_obj_invoker = static_cast<const cocos2d::CCObject*>(invoker);
//        printf("[YJRAND](%8u)i:%-30s|o:%15u|r:%15f|\n", p_obj_invoker==NULL?0:p_obj_invoker->m_uID, p_obj_invoker==NULL?"NA":typeid(*p_obj_invoker).name(), originRand, resultRand);
//        LOG_TO_FILE("zm_rand.txt", "[YJRAND](%8u)i:%-30s|o:%15u|r:%15f|\n", p_obj_invoker==NULL?0:p_obj_invoker->m_uID, p_obj_invoker==NULL?"NA":typeid(*p_obj_invoker).name(), originRand, resultRand);
        YJ_LOG_BATTLE_ONE_LINE(
                               "|%15s|%-30s - %8u|org:%16u|rsl:%16f|",
                               "[RAND]",
                               p_obj_invoker==NULL?"NA":typeid(*p_obj_invoker).name(),
                               p_obj_invoker==NULL?0:p_obj_invoker->m_uID,
                               originRand,
                               resultRand
                               );

    }
    s_orignRandLog.push_back(originRand);
    s_randResultLog.push_back(resultRand);
    s_lastRandResult = resultRand;
}

extern const std::vector<unsigned>& yjGetOriginRandLog() {
    return s_orignRandLog;
}

extern const std::vector<float>& yjGetRandResultLog() {
    return s_randResultLog;
}

extern float yjGetLastRandResult() {
    return s_lastRandResult;
}

#endif