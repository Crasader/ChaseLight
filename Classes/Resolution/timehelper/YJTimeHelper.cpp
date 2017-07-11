//
//  YJTimeHelper.cpp
//  4399zmxyx
//
//  Created by mimicry on 4/10/13.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//

#include "YJTimeHelper.h"
#include "YJCookedNum.h"
#include "YJConstant.h"
#include "YJGlobalManager.h"
#include "cocos2d.h"
#include <time.h>
#include "YJStringHelper.h"

const long INVALID_TIME = 0;
static YJCKLong g_lastUpdatedServerTimeStamp;
static YJCKLong g_lastUpdatedLocalTimeStamp;

int yjGetDaysRelationship(long day1UnixSecs, long day2UnixSecs, long dayMileStoneSecs) {
	time_t day_1_unix_secs = day1UnixSecs - dayMileStoneSecs;
    tm* day1_tm = localtime(&day_1_unix_secs);
    int day1_yday = day1_tm->tm_yday;
    int day1_year = day1_tm->tm_year;

	time_t day_2_unix_secs = day2UnixSecs - dayMileStoneSecs;
    tm* day2_tm = localtime(&day_2_unix_secs);
    int day2_yday = day2_tm->tm_yday;
    int day2_year = day2_tm->tm_year;
    
    if (day1_year > day2_year) return 1;
    if (day1_year < day2_year) return -1;
    if (day1_yday > day2_yday) return 1;
    if (day1_yday < day2_yday) return -1;
    return 0;
}

int yjGetRelationshipBetweenTodayAndSpecifiedDay(long dayUnixSecs, bool useTodayTimeOnServer, long dayMileStoneSecs) {
    time_t now;
    if (useTodayTimeOnServer)
        now = yjGetServerNow();
    else
        time(&now);
    return yjGetDaysRelationship(now, dayUnixSecs, dayMileStoneSecs);
}

void yjInitServerTimeStamp(){
    g_lastUpdatedServerTimeStamp = INVALID_TIME;
    g_lastUpdatedLocalTimeStamp = INVALID_TIME;    
}

bool yjUpdateServerTimeStamp(long currentTime){
    bool ret = true;
    /* 记录游戏时间开始的服务器时间戳，当等待中的请求数量为0时，则为新的一个游戏时间段记录的开始 */
    if (GlobalMgr->getIsDetectTimeOpened()) {
        if (g_lastUpdatedLocalTimeStamp != INVALID_TIME || g_lastUpdatedServerTimeStamp != INVALID_TIME) {
            if (GlobalMgr->getLastRecordServiceTime() == 0 || GlobalMgr->getRequestWaitingResponeCnt() <= 0) {
                GlobalMgr->setLastRecordServiceTime(currentTime);
                GlobalMgr->startDetectTime();
            }
        }
        /*
//        if (g_lastUpdatedServerTimeStamp == INVALID_TIME && g_lastUpdatedLocalTimeStamp == INVALID_TIME) {
//            ret = true;
//        }
//        else {
//            //** 是否开启时间检测在读取存档的时候返回，因此在读取存档之后，则开始记录游戏时间
//            if (GlobalMgr->getLastRecordServiceTime() == 0) {
//                GlobalMgr->setLastRecordServiceTime(currentTime);
//                GlobalMgr->startDetectTime();
//            }
//            else {
//                
//                //** 判断加速的这部分逻辑交由服务器执行
//                {
//                    //** 由于网络原因，可能会导致误杀（网络非常差的情况下，游戏时间一直在记录着，胆识服务器事实上很早就返回了，只是客户端一直没有收到，这样在收到的时候就会判断游戏时间差大于服务器时间差）
//                    //** 因此，在开启时检测的情况下，记录发送请求时的游戏时间差，请求成功后将game_dt赋值为记录下的时间差，相当于认为服务器在游戏发送请求的一瞬间就回执了。
//                    
//                    //** WARNNING!! 由于加速本身就是将整个系统时间也加速了，因此当玩家加速完之后，可以将游戏挂后台等待过加速的时间之后再发起请求，这样的话，也时检测不出加速的。
//                    float game_dt = GlobalMgr->getLastRequestDetectTime();
//                    long server_dt = currentTime - GlobalMgr->getLastRecordServiceTime();
//                    
//                    if (game_dt - server_dt > 1) {
//                        ret = false;
//                    }
//                }
//
//                //** 如果等待中的请求数量大于0,则表示，这个游戏时间段不能结束， 游戏时间还在继续记录，每个请求的比较，都是和之前记录下来的服务器时间进行比较
//                //** 当等待中的请求数量为0时,则表示这个游戏时间段结束,将这次的服务器时间记录下来，并且重新开始计算游戏时间
//                if (GlobalMgr->getRequestWaitingResponeCnt() <= 0) {
//                    GlobalMgr->setLastRecordServiceTime(currentTime);
//                    GlobalMgr->startDetectTime();
//                }
//                
////                YJLOG("GAME_DELTA_TIME:%f, SERVER_DELTA_TIME:%ld, WAITING_COUNT:%d", game_dt, server_dt, GlobalMgr->getRequestWaitingResponeCnt());
//            }
//            
//        }
		*/
    }

    g_lastUpdatedServerTimeStamp = currentTime;
    g_lastUpdatedLocalTimeStamp = time(NULL);
    
    return ret;
}

long yjGetServerTime(long localTime){
    if( INVALID_TIME==g_lastUpdatedLocalTimeStamp || INVALID_TIME==g_lastUpdatedServerTimeStamp){
        return INVALID_TIME;
    }
    if( localTime < g_lastUpdatedLocalTimeStamp ){
        return INVALID_TIME;//< If the player modify the system time to an earlier time,let the current time be 0(in normal it means 1900).Is it better to return g_lastUpdatedServerTimeStamp instead?
    }
    return g_lastUpdatedServerTimeStamp + ( localTime - g_lastUpdatedLocalTimeStamp );
}

long yjGetServerNow(){
    return yjGetServerTime(time(NULL));
}

long yjGetTodayStartTime(bool returnTimeOnServer, long dayMileStoneSecs)
{
    time_t now;
    if (returnTimeOnServer)
        now = yjGetServerNow();
    else
        time(&now);
    
    tm* today_tm = localtime(&now);
    today_tm->tm_hour = 0;
    today_tm->tm_min = 0;
    today_tm->tm_sec = 0;
    
    now = mktime(today_tm);
    return now + dayMileStoneSecs;
}

long yjGetTodayEndTime(bool returnTimeOnServer, long dayMileStoneSecs)
{
    time_t now;
    if (returnTimeOnServer)
        now = yjGetServerNow();
    else
        time(&now);
    
    tm* today_tm = localtime(&now);
    today_tm->tm_hour = 23;
    today_tm->tm_min = 59;
    today_tm->tm_sec = 59;
    
    now = mktime(today_tm);
    return now + dayMileStoneSecs;
}

std::string yjGetTimeStringFormat1(long time)
{
    char time_buf[128];
	time_t time_ = time;
    tm* time_tm = localtime(&time_);
    int mon = time_tm->tm_mon + 1;
    int day = time_tm->tm_mday;
    int hour = time_tm->tm_hour;
    int min = time_tm->tm_min;
    int sec = time_tm->tm_sec;
    
    snprintf(time_buf, sizeof(time_buf), "%d月%d日 %02d:%02d:%02d",mon,day,hour,min,sec);
    return std::string(time_buf);
}

std::string yjGetTimeStringFormat2(long time)
{
	char time_buf[128];
	time_t time_ = time;
	tm* time_tm = localtime(&time_);
	int mon = time_tm->tm_mon + 1;
	int day = time_tm->tm_mday;
	int year = time_tm->tm_year + 1900; 
	snprintf(time_buf, sizeof(time_buf), YJUSTR("%d年%d月%d日 "), year, mon, day);
	return std::string(time_buf);
}

std::string yjGetTimeStringFormat3(long time)
{
    char time_buf[128];
	time_t time_ = time;
	tm* time_tm = localtime(&time_);
    int hour = time_tm->tm_hour;
    int min = time_tm->tm_min;
    int sec = time_tm->tm_sec;
	snprintf(time_buf, sizeof(time_buf), YJUSTR("%02d:%02d:%02d "), hour, min, sec);
	return std::string(time_buf);
}

std::string yjConvertSeceondsToStringFormat3(long seconds)
{
    int rest_seconds = seconds % 60;
    int rest_minutes = seconds / 60;
    if( rest_minutes >= 60 ){
        rest_minutes = rest_minutes % 60;
    }
    int rest_hours = seconds / 3600;
    return GET_FORMAT_STRING(128,"%02d:%02d:%02d",rest_hours,rest_minutes,rest_seconds);
}

std::string yjGetTimeStringFormat4(long time)
{
    char time_buf[128];
	time_t time_ = time;
	tm* time_tm = localtime(&time_);
    int hour = time_tm->tm_hour;
    int min = time_tm->tm_min;
	snprintf(time_buf, sizeof(time_buf), YJUSTR("%02d:%02d "), hour, min);
	return std::string(time_buf);
}

std::string yjGetTimeStringFormat5(long time)
{
    char time_buf[128]={0};
	time_t time_ = time;
	tm* time_tm = localtime(&time_);
    int min = time_tm->tm_min;
    int sec = time_tm->tm_sec;
	snprintf(time_buf, sizeof(time_buf), YJUSTR("%02d:%02d "), min, sec);
	return std::string(time_buf);
}