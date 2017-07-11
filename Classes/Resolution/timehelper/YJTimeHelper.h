//
//  YJTimeHelper.h
//  4399zmxyx
//
//  Created by mimicry on 4/10/13.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//

#ifndef ___399zmxyx__YJTimeHelper__
#define ___399zmxyx__YJTimeHelper__

#include <string>

extern const long INVALID_TIME;

#define YJ_FIVE_OF_THE_CLOCK (YJCI4(3,6,0,0)*5)

// Return   0 -- the same day
//          1 -- day1 > day2
//          -1 -- day1 < day2
// @param day1UnixSecs -- The first day time in unix seconds.
//        day2UnixSecs -- The second day time in unix sceonds.
//        dayMileStoneSecs -- The 'milestone' time to separate two days. (0~86399)
extern int yjGetDaysRelationship(long day1UnixSecs, long day2UnixSecs, long dayMileStoneSecs = 0);

// Return   0 -- the same day as today
//          1 -- today > specified day
//          -1 -- today < specified day
// @param dayUnixSecs -- The day time to be compared with today in unix seconds.
//        useTodayTimeOnServer -- True if use the server timestamp instead device local's.
//        dayMileStoneSecs -- The 'milestone' time to separate two days. (0~86399)
extern int yjGetRelationshipBetweenTodayAndSpecifiedDay(long dayUnixSecs, bool useTodayTimeOnServer = true, long dayMileStoneSecs = 0);

// Init the server time stamp
extern void yjInitServerTimeStamp();

// Update server time
extern bool yjUpdateServerTimeStamp(long currentTime);

// Get server time according to the last updated server time
extern long yjGetServerTime(long localTime);

// Get the current of the server according to the last updated server time
extern long yjGetServerNow();

// Get today 0:00:00 + dayMileStoneSecs time
extern long yjGetTodayStartTime(bool returnTimeOnServer=true, long dayMileStoneSecs = 0);

// Get today 23:59:59 + dayMileStoneSecs time
extern long yjGetTodayEndTime(bool returnTimeOnServer=true, long dayMileStoneSecs = 0);

/* Get time string as the format : %d月%d日 %02d:%02d:%02d */
/* param : unix sec */
extern std::string yjGetTimeStringFormat1(long);

/* Get time string as the format : %d年%d月%日 */
/* param : unix sec */
extern std::string yjGetTimeStringFormat2(long);

/* Get time string as the format : %02h:%02m:%02s */
/* param : unix sec */
extern std::string yjGetTimeStringFormat3(long);
extern std::string yjConvertSeceondsToStringFormat3(long seconds);

/* Get time string as the format : %02h:%02m */
/* param : unix sec */
extern std::string yjGetTimeStringFormat4(long);

/* Get time string as the format : %02m:%02s */
/* param : unix sec */
extern std::string yjGetTimeStringFormat5(long);

#endif /* defined(___399zmxyx__YJTimeHelper__) */
