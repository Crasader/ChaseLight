//
//  YJWebViewHelper.mm
//  4399zmxyx
//
//  Created by Light0457 on 13-8-31.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#include "YJIOSWebView.h"
#include "cocos2d.h"
#include "YJEventConstant.h"
USING_NS_CC;

@interface YJIOSWebViewNotificationCenter : NSObject {}
+ (YJIOSWebViewNotificationCenter*) sharedCenter;

- (void) addObserver:(NSString*)tag;
- (void) postNotification:(NSNotification *)notification;
@end

static YJIOSWebViewNotificationCenter* g_center = nil;

@implementation YJIOSWebViewNotificationCenter
+ (YJIOSWebViewNotificationCenter*) sharedCenter
{
    @synchronized(self)
    {
        if (nil==g_center) {
            g_center = [[YJIOSWebViewNotificationCenter alloc] init];
        }
    }
    return g_center;
}

- (void) addObserver:(NSString *)tag
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(postNotification:)
                                                 name:tag object:nil];
}

- (void) postNotification:(NSNotification *)notification
{
    
    std::string tag_str;
    if (nil!=notification) {
        tag_str = [[notification object] cStringUsingEncoding:NSUTF8StringEncoding];
    }
    CCString* tagCCStr = CCString::create(tag_str);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(YJ_EVENT_WEBVIEW_CLOSED, tagCCStr);
}

@end

void yjOpenWebView(const char* url, const char* tag){
    YJIOSWebView* web_view = [[[YJIOSWebView alloc]init]autorelease];
    YJIOSWebFrameView* web_view_window = [[[YJIOSWebFrameView alloc] initWithWebView:web_view isNeedTopBar:YES] autorelease];
    if (tag==NULL) {
        web_view_window.tag = nil;
        tag = "";
    }
    else
        web_view_window.webViewTag = [NSString stringWithUTF8String:tag];
    UIView* root_view = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    [root_view addSubview:web_view_window];
    [web_view loadURL:[NSString stringWithUTF8String:url]];
    
    [[YJIOSWebViewNotificationCenter sharedCenter] addObserver:[NSString stringWithUTF8String:tag]];
}

void yjOpenStrategyWebView(const char* url, const char* tag){
    YJIOSWebView* web_view = [[[YJIOSWebView alloc]init]autorelease];
    YJIOSWebFrameView* web_view_window = [[[YJIOSWebFrameView alloc] initWithWebView:web_view isNeedTopBar:NO] autorelease];
    if (tag==NULL) {
        web_view_window.tag = nil;
        tag = "";
    }
    else
        web_view_window.webViewTag = [NSString stringWithUTF8String:tag];
    UIView* root_view = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    [root_view addSubview:web_view_window];
    [web_view loadURL:[NSString stringWithUTF8String:url]];
    
    [[YJIOSWebViewNotificationCenter sharedCenter] addObserver:[NSString stringWithUTF8String:tag]];
}