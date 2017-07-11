//
//  YJStringHelper.h
//  4399zmxyx
//
//  Created by mimicry on 12/14/12.
//  Copyright (c) 2012 4399 ios. All rights reserved.
//

#ifndef ___399zmxyx__YJStringHelper__
#define ___399zmxyx__YJStringHelper__
#include <string>
#include "cocos2d.h"

extern bool yjIsUTF8StringInZhHan(const char* utf8_string);

extern void yjCaculateLabelSize(const char * pText,
                                const char * pFontName,
                                int nFontSize,
                                unsigned int nConstrainWidth,
                                unsigned int nConstrainHeight,
                                cocos2d::CCTextAlignment alignment,
                                cocos2d::CCVerticalTextAlignment vertAlignment,
                                unsigned int* pDimensionWidthOut,
                                unsigned int* pDimensionHeightOut);

extern std::string yjMD5(const std::string str);

extern void yjStringReplace(std::string & str, const std::string & strsrc, const std::string &strdst);

#ifdef WIN32
extern std::string yjWinConvertGBKToUTF8(const char* pGBKCString);
#define YJUSTR(cstr) yjWinConvertGBKToUTF8(cstr).c_str()
#else
#define YJUSTR(cstr) cstr
#endif

template <int BufSize>
const char* yjGetFormatCString(const char * pszFormat, ...)
{
    static char sz_buf[BufSize] = {0};
    memset(sz_buf, 0, sizeof(sz_buf));
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(sz_buf, BufSize, pszFormat, ap);
    va_end(ap);
    return sz_buf;
}
#define GET_FORMAT_CSTRING(bufSize,format, ...) yjGetFormatCString<bufSize>(format,##__VA_ARGS__)

template <int BufSize>
std::string yjGetFormatString(const char * pszFormat, ...)
{
    char sz_buf[BufSize] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(sz_buf, BufSize, pszFormat, ap);
    va_end(ap);
    return std::string(sz_buf);
}
#define GET_FORMAT_STRING(bufSize,format, ...) yjGetFormatString<bufSize>(format,##__VA_ARGS__)


#endif /* defined(___399zmxyx__YJStringHelper__) */
