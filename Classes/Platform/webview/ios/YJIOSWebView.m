//
//  YJIOSWebView.cpp
//  4399zmxyx
//
//  Created by Light0457 on 13-8-31.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#include "YJIOSWebView.h"

#pragma mark - YJIOSWebFrameView
@implementation YJIOSWebFrameView

- (id)initWithWebView:(YJIOSWebView*)webView isNeedTopBar:(BOOL)needTopBar{
    CGRect screenBounds = [UIScreen mainScreen].bounds;
    CGFloat width = CGRectGetWidth(screenBounds)  ;
    CGFloat height = CGRectGetHeight(screenBounds) ;
    UIInterfaceOrientation interfaceOrientation = [UIApplication sharedApplication].statusBarOrientation;
    if (UIInterfaceOrientationIsLandscape(interfaceOrientation)) {
        screenBounds.size = CGSizeMake(height, width);
    }
    if (self = [super initWithFrame:screenBounds]) {
        NSBundle* bundle = [NSBundle bundleWithPath:
                            [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"YJIOSWebViewRes.bundle"]];
        NSAssert(nil != bundle, @"Resource bundle is missing");
        if (nil == bundle) {
            [self release];
            return nil;
        }
        
        CGSize frameSize = screenBounds.size;
        CGSize closeButtonSize = CGSizeMake(36, 34);
        CGPoint closeButtonOffset = CGPointMake(frameSize.width-33, 0);
//        CGSize goBackButtonSize = CGSizeMake(70, 28);
//        CGPoint goBackButtonOffset = CGPointMake(frameSize.width-80, 8.f);
        CGSize top_bar_size = CGSizeMake(frameSize.width, 36);
        
        
        // Black mask
        UIView *blackBG = [[UIView alloc] initWithFrame:screenBounds];
        [blackBG setBackgroundColor:[UIColor blackColor]];
        [blackBG setAlpha:0.7f];
        [self addSubview:blackBG];
        [blackBG release];
        
        // Frame
        UIImageView *bgImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, frameSize.width, frameSize.height)];
        NSString *path = [bundle pathForResource:@"wnd_common_bg" ofType:@"png"];
        NSAssert(path != nil, @"Resource is not found");
        [bgImageView setImage:[UIImage imageWithContentsOfFile:path]];
        [bgImageView setUserInteractionEnabled:YES];
        [bgImageView setExclusiveTouch:YES];
        [self addSubview:bgImageView];
        bgImageView.center = CGPointMake(self.bounds.size.width*0.5, self.bounds.size.height*0.5);
        [bgImageView release];
        
        
        iosWebView = webView;
        if (needTopBar) {
            // Top bar
            UIImageView* top_bar_image_view = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, frameSize.width, top_bar_size.height)];
            path = [bundle pathForResource:@"top_bar_bg" ofType:@"png"];
            NSAssert(path!=nil,@"Resouce is not found");
            [top_bar_image_view setImage:[UIImage imageWithContentsOfFile:path]];
            [self addSubview:top_bar_image_view];
            [top_bar_image_view release];
            
            // web view
            if (nil != webView) {
                [webView loadWithFrame:CGRectMake(0, 0, frameSize.width, frameSize.height - top_bar_size.height)];
                [webView setWebViewDelegate:self];
                [self addSubview:webView];
                webView.center = CGPointMake(self.bounds.size.width*0.5, (self.bounds.size.height+ top_bar_size.height)*0.5);
            }
            else {
                NSAssert(NO, @"Login view is required");
            }
            
        }
        else {
            // web view
            if (nil != webView) {
                [webView loadWithFrame:CGRectMake(0, 0, frameSize.width, frameSize.height)];
                [webView setWebViewDelegate:self];
                [self addSubview:webView];
                webView.center = CGPointMake(self.bounds.size.width*0.5, self.bounds.size.height*0.5);
            }
            else {
                NSAssert(NO, @"Login view is required");
            }

//            // Go back button
//            path = [bundle pathForResource:@"comm_close_btn" ofType:@"png"];
//            NSAssert(path != nil, @"Resource is not found");
//            goBackButton = [UIButton buttonWithType:UIButtonTypeCustom];
//            [goBackButton setFrame:
//             CGRectMake(bgImageView.frame.origin.x + closeButtonOffset.x,
//                        bgImageView.frame.origin.y + closeButtonOffset.y,
//                        closeButtonSize.width, closeButtonSize.height)];
//            [goBackButton addTarget:self action:@selector(onGoBack) forControlEvents:UIControlEventTouchUpInside];
//            [goBackButton setImage:[UIImage imageWithContentsOfFile:path] forState:UIControlStateNormal];
////            goBackButton.hidden = YES;
//            
//            [self addSubview:goBackButton];
        }

        // Close button
        path = [bundle pathForResource:@"comm_close_btn" ofType:@"png"];
        NSAssert(path != nil, @"Resource is not found");
        closeButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [closeButton setFrame:
         CGRectMake(bgImageView.frame.origin.x + closeButtonOffset.x,
                    bgImageView.frame.origin.y + closeButtonOffset.y,
                    closeButtonSize.width, closeButtonSize.height)];
        [closeButton addTarget:self action:@selector(onClose) forControlEvents:UIControlEventTouchUpInside];
        [closeButton setImage:[UIImage imageWithContentsOfFile:path] forState:UIControlStateNormal];
        
        [self addSubview:closeButton];

        self.userInteractionEnabled = YES;
        self.multipleTouchEnabled = YES;
        self.exclusiveTouch = YES;
    }
    return self;
}

- (void)webViewCancelLoad
{
    if (self.webViewTag!=nil) {
        [[NSNotificationCenter defaultCenter] postNotificationName:self.webViewTag object:self.webViewTag];
    }

    [self onClose];
}

- (void)showViewGoBackBtn:(BOOL)enable
{
    if (nil != goBackButton) {
        goBackButton.hidden = !enable;
    }
}

- (void)setGoBackBtnEnable:(BOOL)enable
{
    if (nil != goBackButton) {
        goBackButton.enabled = enable;
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    //** Swallow touch
    [[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    [[UIApplication sharedApplication] endIgnoringInteractionEvents];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{

}

- (void) onClose
{
    if ( nil!=iosWebView ) {
        [iosWebView setWebViewDelegate:nil];
    }
    [self removeFromSuperview];
}

- (void) onGoBack
{
    if ( nil!=iosWebView ) {
        [iosWebView onGoBackBtnTouched];
    }
}
@end

#pragma mark - YJIOSWebView
@implementation YJIOSWebView

@synthesize WebViewDelegate;

- (id)init
{
    if( self = [super init])
    {
        self.haveShowErrorMsg = NO;
        NSBundle* bundle = [NSBundle bundleWithPath:
                            [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"YJIOSWebViewRes.bundle"]];
        NSAssert(nil != bundle, @"Resource bundle is missing");
        if (nil == bundle) {
            [self release];
            return nil;
        }
        
        CGRect screen_rect = [UIScreen mainScreen].bounds;
        CGFloat width = CGRectGetWidth(screen_rect);
        CGFloat height = CGRectGetHeight(screen_rect);

        //** Init holder img
        m_holderImg = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, width*0.5f, height*0.5f)];
        NSString* imagePath = [bundle pathForResource:@"loading_holder" ofType:@"png"];
        NSAssert(nil != imagePath, @"");
        [m_holderImg setImage:[UIImage imageWithContentsOfFile:imagePath]];
//        [m_holderImg setContentMode:UIViewContentModeScaleAspectFit];
        [self addSubview:m_holderImg];
        m_holderImg.hidden = NO;

        //** Init web view
        UIInterfaceOrientation interface_orientation = [UIApplication sharedApplication].statusBarOrientation;
        if( UIInterfaceOrientationIsLandscape(interface_orientation) ){
            screen_rect.size = CGSizeMake(height,width);
        }
        self.userInteractionEnabled = YES;
        self.multipleTouchEnabled = YES;
        self.exclusiveTouch = YES;
        m_webView = [[UIWebView alloc] initWithFrame:screen_rect];        
        m_webView.delegate = self;
        m_webView.multipleTouchEnabled = YES;
        [m_webView setUserInteractionEnabled:YES];
        m_webView.autoresizingMask = (UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleTopMargin | UIViewAutoresizingFlexibleBottomMargin);
        
        m_webView.autoresizesSubviews = NO;
        [m_webView setScalesPageToFit:NO];
        
        [m_webView setBackgroundColor:[UIColor clearColor]];
        m_webView.opaque = NO;
        
        [self addSubview:m_webView];        
    }
    return self;
}

- (void)loadURL:(NSString *)url
{
    NSURLRequest* request =[NSURLRequest requestWithURL:[NSURL URLWithString:url]];
    self.requestUrl = request;
    [NSURLConnection connectionWithRequest:request delegate:self];
//    [m_webView loadRequest:request];
}

- (void)loadWithFrame:(CGRect)frame
{
    self.frame = frame;
    m_webView.frame = frame;
    m_holderImg.frame = frame;
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;
    
    if (httpResponse.statusCode < 200 || httpResponse.statusCode >= 300) {
        NSString* str_message = [NSString stringWithFormat:@"获取网页失败"];
        UIAlertView* network_msg_alert_view = [[UIAlertView alloc] initWithTitle:@"温馨提示" message:str_message delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil , nil];
        [network_msg_alert_view show];
        [network_msg_alert_view release];
    }
    else
    {
        [m_webView loadRequest:self.requestUrl];
    }
    
    [connection cancel];
}

- (void)webViewDidStartLoad:(UIWebView*)webView
{
    if( m_indicator == nil )
    {
        m_indicator = [[YJLibIndicatorView alloc] initWithFrame:CGRectMake(m_webView.frame.size.width*0.5-60, m_webView.frame.size.height*0.5-60, 100, 100)];
        [m_indicator setCenter:m_webView.center];
        [m_indicator setIndicatorText:@"加载中..."];
    }
    [m_webView addSubview:m_indicator];
    [WebViewDelegate setGoBackBtnEnable:NO];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    if( m_indicator.superview != nil )
    {
        [m_indicator removeFromSuperview];
    }
    m_holderImg.image = nil;
    m_holderImg.hidden = YES;
    [WebViewDelegate setGoBackBtnEnable:YES];
}

- (void)moviePlayerDidExitFullscreen:(NSNotification*)notification
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"UIMoviePlayerControllerDidExitFullscreenNotification" object:nil];
    [self onGoBackBtnTouched];
}

- (void)onGoBackBtnTouched
{
    if (nil!=m_webView && m_webView.canGoBack) {
        [m_webView goBack];
//        if ( nil!=WebViewDelegate) {
//            [WebViewDelegate showViewGoBackBtn:NO];
//        }
    }
    else {
        if( nil != WebViewDelegate ){
            [WebViewDelegate webViewCancelLoad];
        }
    }
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    if( m_indicator != nil ){
        [m_indicator removeFromSuperview];
    }
    
    if( error.code == 102 ){
        return;
    }
    
    if (error.code == NSURLErrorCancelled) {
        return;
    }
    
    if (self.haveShowErrorMsg) {
        return;
    }
    self.haveShowErrorMsg = YES;
    
    NSString* str_message = [NSString stringWithFormat:@"获取网页失败"];
    if( error.code == -1001 ){
        NSLog(@"error %@",[error description]);
        str_message = [NSString stringWithFormat:@"连接超时"];
    }
    
    UIAlertView* network_msg_alert_view = [[UIAlertView alloc] initWithTitle:@"温馨提示" message:str_message delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil , nil];
    [network_msg_alert_view show];
    [network_msg_alert_view release];
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSString* urlStr = request.URL.absoluteString;
    if( [urlStr compare:@"zmxy://close"] == NSOrderedSame )
    {
        if( nil != WebViewDelegate ){
            [WebViewDelegate webViewCancelLoad];
        }
    }
    else if ( [urlStr rangeOfString:@"http://player.youku.com" options:NSCaseInsensitiveSearch].length > 0) {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:@"UIMoviePlayerControllerDidExitFullscreenNotification" object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(moviePlayerDidExitFullscreen:) name:@"UIMoviePlayerControllerDidExitFullscreenNotification" object:nil];
        
//        if ( nil != WebViewDelegate ) {
//            [WebViewDelegate showViewGoBackBtn:YES];
//        }

    }
    return YES;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if( nil != WebViewDelegate ){
        [WebViewDelegate webViewCancelLoad];
    }
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"UIMoviePlayerControllerDidExitFullscreenNotification" object:nil];
    m_webView.delegate = nil;
    [m_webView release];
    [m_indicator release];
    [m_holderImg release];
    
    [super dealloc];
}

@end