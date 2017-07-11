//
//  TimeUtilRef.h
//  RollingBall
//
//  Created by Reyn-Mac on 2017/7/5.
//
//

#ifndef TimeUtilRef_h
#define TimeUtilRef_h

#include "CCBase.h"

namespace TimeUtil {
    /*时间定义*/
    const int SECONDS_IN_MINUTE = 60;
    const int MINUTES_IN_HOUR   = 60;
    const int HOURS_IN_DAY      = 24;
    const int SECONDS_IN_HOUR   = (SECONDS_IN_MINUTE*MINUTES_IN_HOUR);
    const int SECONDS_IN_DAY    = (HOURS_IN_DAY*SECONDS_IN_HOUR);
    
    /*格式枚举*/
    enum class TimeFormat {
        ALL,    //全部显示
        HMS,    //时分秒
        HM,     //时分
        MS,     //分秒
        S,      //秒
        AUTO,   //自动
    };
    
    /*单位转换*/
    static unsigned int day(unsigned int sec) {
        return sec / SECONDS_IN_DAY;
    }
    static unsigned int hour(unsigned int sec) {
        return (sec / SECONDS_IN_HOUR) % HOURS_IN_DAY;
    }
    static unsigned int minute(unsigned int sec) {
        return (sec / MINUTES_IN_HOUR) % SECONDS_IN_MINUTE;
    }
    static unsigned int second(unsigned int sec) {
        return (sec % SECONDS_IN_MINUTE);
    }
    
    /*格式转换,内部具体实现*/
    namespace {
        static const char* dhms(unsigned int sec) {
            return StringUtils::format("%d%s%02d%s%02d%s%02d%s", day(sec), TEXT_DAY, hour(sec), TEXT_HOU, minute(sec), TEXT_MIN, second(sec), TEXT_SEC).c_str();
        }
        
        static const char* hms(unsigned int sec) {
            return StringUtils::format("%02d%s%02d%s%02d%s", hour(sec), TEXT_HOU, minute(sec), TEXT_MIN, second(sec), TEXT_SEC).c_str();
        }
        
        static const char* hm(unsigned int sec) {
            return StringUtils::format("%02d%s%02d%s", hour(sec), TEXT_HOU, minute(sec), TEXT_MIN ).c_str();
        }
        
        static const char* ms(unsigned int sec) {
            return StringUtils::format("%02d%s%02d%s", minute(sec), TEXT_MIN, second(sec), TEXT_SEC).c_str();
        }
        
        static const char* s(unsigned int sec) {
            return StringUtils::format("%02d%s", second(sec), TEXT_SEC).c_str();
        }
        
        static const char* automatic(unsigned int sec) {
            if(day(sec) > 0) {
                return dhms(sec);
            }
            
            if(hour(sec) > 0) {
                return hms(sec);
            }
            
            if(minute(sec) > 0) {
                return ms(sec);
            }
            
            return s(sec);
        }
    }
    

    /*格式转换,对外接口*/
    static const char* format(int sec, TimeFormat format=TimeFormat::AUTO) {
        switch (format) {
            case TimeFormat::ALL:
                return dhms(sec);
                break;
            
            case TimeFormat::HMS:
                return hms(sec);
                break;
                
            case TimeFormat::HM:
                return hm(sec);
                break;
                
            case TimeFormat::MS:
                return ms(sec);
                break;
                
            case TimeFormat::S:
                return s(sec);
                break;
                
            case TimeFormat::AUTO:
            default:
                return automatic(sec);
                break;
        }
    }
}




#endif /* TimeUtilRef_h */
