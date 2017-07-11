//
//  YJAppstoreHelper.cpp
//  4399zmxyx
//
//  Created by longyan on 13-12-11.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#include "YJAppstoreHelper.h"
#include "CCPlatformConfig.h"
#include <assert.h>
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
void yjAppInit(){
	assert(0); //** Appstore method is not implement for platform other than iOS!
}
void yjAppRequestProductData() {
	assert(0); //** Appstore method is not implement for platform other than iOS!
}
void yjAppRequestPayment(int productIdx, char* orderID, int amount) {
	assert(0); //** Appstore method is not implement for platform other than iOS!
}
bool yjAppIsProductsEmpty() {
	assert(0); //** Appstore method is not implement for platform other than iOS!
	return false;
}
bool yjAppProductsContainsID(int productIdx) {
	assert(0); //** Appstore method is not implement for platform other than iOS!
	return false;
}
#endif