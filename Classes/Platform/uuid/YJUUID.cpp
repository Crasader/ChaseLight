//
//  YUUID.cpp
//  4399zmxyx
//
//  Created by mimicry on 11/9/12.
//  Copyright (c) 2012 4399 ios. All rights reserved.
//

#include "YJUUID.h"
#include "CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/YJUUIDAndroid_cpp.h"
#elif (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
#ifdef WIN32
#include <Windows.h> 
#include <winerror.h>
#include <iphlpapi.h>
#pragma comment(lib, "Iphlpapi.lib")
std::string yjFetchUUIDString(int* errorCode){

	static bool b_is_uuid_generated = false;
	std::string uuid_str = "win32";
	if (!b_is_uuid_generated) {
		char mac[100];
		::memset(mac, 0, sizeof(mac));
		ULONG outBufLen = 0;
		DWORD dwRetVal = 0;
		IP_ADAPTER_INFO* pAdapterInfos = (IP_ADAPTER_INFO*) malloc(sizeof(IP_ADAPTER_INFO));

		// retry up to 5 times, to get the adapter infos needed
		for( int i = 0; i < 5 && (dwRetVal == ERROR_BUFFER_OVERFLOW || dwRetVal == NO_ERROR); ++i )
		{
			dwRetVal = GetAdaptersInfo(pAdapterInfos, &outBufLen);
			if( dwRetVal == NO_ERROR )
			{
				break;
			}
			else if( dwRetVal == ERROR_BUFFER_OVERFLOW )
			{
				free(pAdapterInfos);
				pAdapterInfos = (IP_ADAPTER_INFO*) malloc(outBufLen);
			}
			else
			{
				pAdapterInfos = 0;
				break;
			}
		}
		if( dwRetVal == NO_ERROR )
		{
			IP_ADAPTER_INFO* pAdapterInfo = pAdapterInfos;
			while( pAdapterInfo )
			{
				IP_ADDR_STRING* pIpAddress = &(pAdapterInfo->IpAddressList);
				while( pIpAddress != 0 )
				{
					::sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X", pAdapterInfo->Address[0], pAdapterInfo->Address[1], pAdapterInfo->Address[2],
						pAdapterInfo->Address[3], pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
					pIpAddress = pIpAddress->Next;
				}
				pAdapterInfo = pAdapterInfo->Next;
			}
		}
		free(pAdapterInfos);
		uuid_str+=mac;
	}
	return uuid_str;
}
#else
std::string yjFetchUUIDString(int* errorCode){
	std::string uuid_str = "not-implement-yet";
	return uuid_str;
}
#endif // WIN32
#endif