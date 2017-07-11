//
//  YJUDID.mm
//  4399zmxyx
//
//  Created by 439906 on 12-10-26.
//  Copyright (c) 2012年 4399 ios. All rights reserved.
//

#include "YJUUID.h"
#include "OpenUDID.h"

std::string yjFetchUUIDString(int* errorCode){
    NSError* error = nil;
    std::string uuid_str = [[YJ_OpenUDID valueWithError:&error] UTF8String];
    if (NULL != errorCode) {
        *errorCode = [error code];
    }
    return uuid_str;
}