//
//  YJStringHelper.cpp
//  4399zmxyx
//
//  Created by mimicry on 12/14/12.
//  Copyright (c) 2012 4399 ios. All rights reserved.
//

#include "YJStringHelper.h"
#include <stdio.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <regex.h>

class YJReg_ {
public:
    YJReg_():_zhHanCompiled(false),_jpCompiled(false){}
    ~YJReg_(){regfree(&_regZhHan);regfree(&_regJp);}
    regex_t* regZhHan() {
        if (!_zhHanCompiled) {
            int cflags = REG_EXTENDED;
            const char* pattern = "^([\xe4-\xe9][\x80-\xbf]{2})+$";
            regcomp(&_regZhHan, pattern, cflags);
            _zhHanCompiled = true;
        }
        return &_regZhHan;
    }
    
    regex_t* regJp() {
        if (!_jpCompiled) {
            int cflags = REG_EXTENDED;
            const char* pattern = "^[\u0800-\u4e00]+$"; //** Wrong! It's used for Unicode.
            regcomp(&_regJp, pattern, cflags);
            _jpCompiled = true;
        }
        return &_regJp;
    }
    
private:
    bool _zhHanCompiled;
    regex_t _regZhHan;
    
    bool _jpCompiled;
    regex_t _regJp;
};

static YJReg_ g_yjReg;

bool yjIsUTF8StringInZhHan(const char* utf8_string) {
    if (NULL == utf8_string) {
        return false;
    }
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    int status;
    
    // Fix jp characters
//    status = regexec(g_yjReg.regJp(), string, nmatch, pmatch, 0);
//    if (status == 0) {
//        return false;
//    }
    
    status = regexec(g_yjReg.regZhHan(), utf8_string, nmatch, pmatch, 0);
    if (status == REG_NOMATCH) {
        return false;
    }
    else if (status == 0){
        return true;
    }
    return false;
}
#else
bool yjIsUTF8StringInZhHan(const char* utf8_string) {
    //< TODO: Not implement yet
    return true;
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <CommonCrypto/CommonDigest.h>

std::string yjMD5(const std::string str) {
    unsigned char md5_sign[16];
    char sign[33];
    CC_MD5(str.c_str(), str.length(), md5_sign);
    snprintf(sign, sizeof(sign), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
             md5_sign[0], md5_sign[1], md5_sign[2], md5_sign[3],
             md5_sign[4], md5_sign[5], md5_sign[6], md5_sign[7],
             md5_sign[8], md5_sign[9], md5_sign[10], md5_sign[11],
             md5_sign[12], md5_sign[13], md5_sign[14], md5_sign[15]);
    return std::string(sign);
}

#else
#include "android/bzfmd5.h"

std::string yjMD5(const std::string str) {
    return bzf_md5(str);
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "android/YJStringHelperAndroid_cpp.h"

void yjCaculateLabelSize(const char * pText,
                         const char * pFontName,
                         int nFontSize,
                         unsigned int nConstrainWidth,
                         unsigned int nConstrainHeight,
                         cocos2d::CCTextAlignment alignment,
                         cocos2d::CCVerticalTextAlignment vertAlignment,
                         unsigned int* pDimensionWidthOut,
                         unsigned int* pDimensionHeightOut) {
    yjCaculateLabelSize_(pText, pFontName, nFontSize, nConstrainWidth, nConstrainHeight, alignment, vertAlignment, pDimensionWidthOut, pDimensionHeightOut);
}
#elif (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)

#ifdef WIN32
#include "CCImage.h"
USING_NS_CC;
void yjCaculateLabelSize(const char * pText,
	const char * pFontName,
	int nFontSize,
	unsigned int nConstrainWidth,
	unsigned int nConstrainHeight,
	cocos2d::CCTextAlignment alignment,
	cocos2d::CCVerticalTextAlignment vertAlignment,
	unsigned int* pDimensionWidthOut,
	unsigned int* pDimensionHeightOut)
{
	CCImage::ETextAlign eAlign;

	if (kCCVerticalTextAlignmentTop == vertAlignment)
	{
		eAlign = (kCCTextAlignmentCenter == alignment) ? CCImage::kAlignTop
			: (kCCTextAlignmentLeft == alignment) ? CCImage::kAlignTopLeft : CCImage::kAlignTopRight;
	}
	else if (kCCVerticalTextAlignmentCenter == vertAlignment)
	{
		eAlign = (kCCTextAlignmentCenter == alignment) ? CCImage::kAlignCenter
			: (kCCTextAlignmentLeft == alignment) ? CCImage::kAlignLeft : CCImage::kAlignRight;
	}
	else if (kCCVerticalTextAlignmentBottom == vertAlignment)
	{
		eAlign = (kCCTextAlignmentCenter == alignment) ? CCImage::kAlignBottom
			: (kCCTextAlignmentLeft == alignment) ? CCImage::kAlignBottomLeft : CCImage::kAlignBottomRight;
	}
	else
	{
		CCAssert(false, "Not supported alignment format!");
		return;
	}

	CCImage* pImage = new CCImage();
	if(NULL == pImage) return;
	pImage->initWithString(pText, (int)nConstrainWidth*CC_CONTENT_SCALE_FACTOR(), (int)nConstrainHeight*CC_CONTENT_SCALE_FACTOR(), eAlign, pFontName, (int)nFontSize);
	if (pDimensionWidthOut) *pDimensionWidthOut = pImage->getWidth();
	if (pDimensionHeightOut) *pDimensionHeightOut = pImage->getHeight();
	CC_SAFE_RELEASE(pImage);
}
#else
void yjCaculateLabelSize(const char * pText,
	const char * pFontName,
	int nFontSize,
	unsigned int nConstrainWidth,
	unsigned int nConstrainHeight,
	cocos2d::CCTextAlignment alignment,
	cocos2d::CCVerticalTextAlignment vertAlignment,
	unsigned int* pDimensionWidthOut,
	unsigned int* pDimensionHeightOut)
{
	//< TODO: Not implement yet
}
#endif
#endif

void yjStringReplace(std::string & str, const std::string & strsrc, const std::string &strdst) {
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();//sub-string to be replaced
    std::string::size_type dstlen = strdst.size();//destination string
    while((pos = str.find(strsrc,pos)) != std::string::npos)
    {
        str.replace(pos,srclen,strdst);
        pos += dstlen;
    }

}

#ifdef WIN32
#include "iconv/iconv.h"
bool IConvConvert(const char *from_charset, const char *to_charset, const char *inbuf, int inlen, char *outbuf, int outlen) 

{

	iconv_t cd = iconv_open(to_charset, from_charset);

	if (cd == 0) return false;

	const char **pin = &inbuf;

	char **pout = &outbuf;

	memset(outbuf,0,outlen);

	size_t ret = iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen);

	iconv_close(cd);

	return ret == (size_t)(-1) ? false : true;

}

std::string yjWinConvertGBKToUTF8(const char* pGBKCString) {
	char textOut[1024];
	bool ret = IConvConvert("gb2312", "utf-8", pGBKCString, strlen(pGBKCString),textOut, 1024);
	return ret ? std::string(textOut) : std::string();
}
#endif
