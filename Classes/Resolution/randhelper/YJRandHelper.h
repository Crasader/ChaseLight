//
//  YJRandHelper.h
//  4399zmxyx
//
//  Created by Mimicry on 8/13/14.
//  Copyright (c) 2014 4399 ios. All rights reserved.
//

#ifndef ___399zmxyx__YJRandHelper__
#define ___399zmxyx__YJRandHelper__

#include <stdlib.h>
#include <vector>

extern void yjSetExternalRandList(const std::vector<unsigned>& randList, unsigned randMin = 0, unsigned randMax = UINT_MAX);
extern void yjSetExternalRandListEnabled(bool enabled);
extern float yjRandomInRangef(float rangeBegin, float rangeEnd, const void* invoker = NULL);

#ifdef DEBUG
extern void yjSetLogRandResultOn(bool isOn); // The log is cleaned in this method
extern const std::vector<unsigned>& yjGetOriginRandLog();
extern const std::vector<float>& yjGetRandResultLog();
extern float yjGetLastRandResult();
#endif

#define YJRANDOM_0_1()              yjRandomInRangef(0.f, 1.f, this)
#define YJRANDOM_0_1_C()            yjRandomInRangef(0.f, 1.f)
#define YJRANDOM_0_1_S(invoker)     yjRandomInRangef(0.f, 1.f, invoker)
#define YJRANDOM_MINUS1_1()         yjRandomInRangef(-1.f, 1.f, this)


#endif /* defined(___399zmxyx__YJRandHelper__) */
