//
//  YJNerworkHelper.mm
//  4399zmxyx
//
//  Created by longyan on 13-7-18.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#ifndef _399zmxyx_YJNerworkHelper_mm
#define _399zmxyx_YJNerworkHelper_mm
#import "YJNetworkHelper.h"
#import "YJLibNetworkReachability.h"

void yjOpenURL(const char* url)
{
    NSString  * nsStringToOpen = [NSString stringWithUTF8String:url ];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:nsStringToOpen]];
}

bool yjIsNetStatus2G()
{
    return [[YJLibNetworkReachability reachabilityForInternetConnection]isReachableVia2G];
}

bool yjIsNetStatus3G()
{
    return [[YJLibNetworkReachability reachabilityForInternetConnection]isReachableVia3G];
}

bool yjIsNetStatusWifi()
{
    return [[YJLibNetworkReachability reachabilityForInternetConnection]isReachableViaWiFi];
}

void yjViewMoreGame()
{
    
}

#endif
