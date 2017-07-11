//
//  YJStringHelper.mm
//  4399zmxyx
//
//  Created by mimicry on 06/25/13.
//  Copyright (c) 2013 4399 ios. All rights reserved.
//

#import "YJStringHelper.h"

static CGSize _calculateStringSize(NSString *str, id font, CGSize *constrainSize)
{
    NSArray *listItems = [str componentsSeparatedByString: @"\n"];
    CGSize dim = CGSizeZero;
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
    : 0x7fffffff;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
    : 0x7fffffff;
    
    
    for (NSString *s in listItems)
    {
        CGSize tmp = [s sizeWithFont:font constrainedToSize:textRect];
        
        if (tmp.width > dim.width)
        {
            dim.width = tmp.width;
        }
        
        dim.height += tmp.height;
    }
    
    return dim;
}


static bool _isValidFontName(const char *fontName)
{
    bool ret = false;
    
    NSString *fontNameNS = [NSString stringWithUTF8String:fontName];
    
    for (NSString *familiName in [UIFont familyNames])
    {
        if ([familiName isEqualToString:fontNameNS])
        {
            ret = true;
            goto out;
        }
        
        for(NSString *font in [UIFont fontNamesForFamilyName: familiName])
        {
            if ([font isEqualToString: fontNameNS])
            {
                ret = true;
                goto out;
            }
        }
    }
    
    out:
    return ret;
}

void yjCaculateLabelSize(const char * pText,
                         const char * pFontName,
                         int nFontSize,
                         unsigned int nConstrainWidth,
                         unsigned int nConstrainHeight,
                         cocos2d::CCTextAlignment alignment, //** Not used in iOS
                         cocos2d::CCVerticalTextAlignment vertAlignment, //** Not used in iOS
                         unsigned int* pDimensionWidthOut,
                         unsigned int* pDimensionHeightOut) {
    
    NSString * str  = [NSString stringWithUTF8String:pText];
    NSString * fntName = [NSString stringWithUTF8String:pFontName];
    CGSize dim, constrainSize;
    constrainSize.width = nConstrainWidth;
    constrainSize.height = nConstrainHeight;
    
    // create the font
    id font;
    font = [UIFont fontWithName:fntName size:nFontSize];
    if (font)
    {
        dim = _calculateStringSize(str, font, &constrainSize);
    }
    else
    {
        fntName = _isValidFontName(pFontName) ? fntName : @"MarkerFelt-Wide";
        font = [UIFont fontWithName:fntName size:nFontSize];
        
        if (! font)
        {
            font = [UIFont systemFontOfSize:nFontSize];
        }
        
        if (font)
        {
            dim = _calculateStringSize(str, font, &constrainSize);
        }
    }
    
    if (!font) {
#ifdef DEBUG
        assert(false);
#endif
    }
        
    // adjust text rect
    if (constrainSize.width > 0 && constrainSize.width > dim.width)
    {
        dim.width = constrainSize.width;
    }
    if (constrainSize.height > 0 && constrainSize.height > dim.height)
    {
        dim.height = constrainSize.height;
    }

    if (NULL != pDimensionWidthOut) {
        *pDimensionWidthOut = dim.width;
    }
    if (NULL != pDimensionHeightOut) {
        *pDimensionHeightOut = dim.height;
    }
    return;
}