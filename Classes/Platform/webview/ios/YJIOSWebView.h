//
//  YJIOSWebView.h
//  4399zmxyx
//
//  Created by Light0457 on 13-8-31.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "YjLibIndicatorView.h"

@protocol YJIOSWebViewDelegate
- (void)webViewCancelLoad;
- (void)showViewGoBackBtn:(BOOL)enable;
- (void)setGoBackBtnEnable:(BOOL)enable;

@end

@interface YJIOSWebView : UIView<UIWebViewDelegate,UIAlertViewDelegate,NSURLConnectionDataDelegate>
{
    UIWebView* m_webView;               //** strong ref
    YJLibIndicatorView* m_indicator;    //** strong ref
    UIImageView* m_holderImg;           //** strong ref
    
}

@property (nonatomic, assign) id<YJIOSWebViewDelegate> WebViewDelegate;
@property (nonatomic, strong) NSURLRequest * requestUrl;
@property (nonatomic) BOOL haveShowErrorMsg;

- (void)loadURL : (NSString*)url;
- (void)loadWithFrame:(CGRect)frame;
- (void)moviePlayerDidExitFullscreen:(NSNotification*)notification;
- (void)onGoBackBtnTouched;
@end


@interface YJIOSWebFrameView : UIView<YJIOSWebViewDelegate> {
    UIImageView *borderLT;
    UIImageView *borderLB;
    UIImageView *borderRT;
    UIImageView *borderRB;
    UIButton *closeButton;
    UIButton *goBackButton;
    YJIOSWebView *iosWebView;
}

@property (nonatomic, retain) NSString *webViewTag;

- (id)initWithWebView:(YJIOSWebView*)webView isNeedTopBar:(BOOL)needTopBar;
- (void)webViewCancelLoad;
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
@end