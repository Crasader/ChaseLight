//
//  YJAppstoreHelper.mm
//  4399zmxyx
//
//  Created by longyan on 13-12-11.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#import "cocos2d.h"
#import <StoreKit/StoreKit.h>
#import <objc/runtime.h>
#import "YJConstant.h"
#import "YJEventConstant.h"
#import "YJAppstoreHelper.h"
#import "AppDelegate.h"

USING_NS_CC;

#define PRODUCTID_IP_1  @"com.zmxyol.one"
#define PRODUCTID_IP_2  @"com.zmxyol.seven"
#define PRODUCTID_IP_3  @"com.zmxyol.two"
#define PRODUCTID_IP_4  @"com.zmxyol.three"
#define PRODUCTID_IP_5  @"com.zmxyol.four"
#define PRODUCTID_IP_6  @"com.zmxyol.five"
#define PRODUCTID_IP_7  @"com.zmxyol.eight"
//#define PRODUCTID_IP_6  @"com.zmxyol.six"

#define PRODUCTID_IPAD_1 @"com.zmxyolhd.one"
#define PRODUCTID_IPAD_2 @"com.zmxyolhd.seven"
#define PRODUCTID_IPAD_3 @"com.zmxyolhd.two"
#define PRODUCTID_IPAD_4 @"com.zmxyolhd.three"
#define PRODUCTID_IPAD_5 @"com.zmxyolhd.four"
#define PRODUCTID_IPAD_6 @"com.zmxyolhd.five"
#define PRODUCTID_IPAD_7 @"com.zmxyolhd.eight"
//#define PRODUCTID_IPAD_6 @"com.zmxyolhd.six"


static NSString* PRODUCTIDS_IP[] = {PRODUCTID_IP_1,PRODUCTID_IP_2,PRODUCTID_IP_3,PRODUCTID_IP_4,PRODUCTID_IP_5,PRODUCTID_IP_6};
static NSString* PRODUCTIDS_IPAD[] = {PRODUCTID_IPAD_1,PRODUCTID_IPAD_2,PRODUCTID_IPAD_3,PRODUCTID_IPAD_4,PRODUCTID_IPAD_5,PRODUCTID_IPAD_6};

#ifdef YJ_TARGET_IPAD
//#define PRODUCTIDS PRODUCTIDS_IPAD
static NSString* PRODUCTIDS[] = {PRODUCTID_IPAD_1,PRODUCTID_IPAD_2,PRODUCTID_IPAD_3,PRODUCTID_IPAD_4,PRODUCTID_IPAD_5,PRODUCTID_IPAD_6,PRODUCTID_IPAD_7};
#else
//#define PRODUCTIDS PRODUCTIDS_IP
static NSString* PRODUCTIDS[] = {PRODUCTID_IP_1,PRODUCTID_IP_2,PRODUCTID_IP_3,PRODUCTID_IP_4,PRODUCTID_IP_5,PRODUCTID_IP_6,PRODUCTID_IP_7};
#endif

static int PRODUCT_COUNT = 7;

static int g_amount = 0;
static std::string g_orderID = "";
static bool g_startPayment = false;
static bool g_bIsFetchingProducts = false;
static int g_product_idx = 0;

//@interface  SKPayment (YJPayment)
//
//@property (nonatomic, retain) NSString* orderID;
//@property (nonatomic, retain) NSNumber* amount;
//@end
//static char ORDER_KEY;
//static char AMOUNT_KEY;
//@implementation SKPayment (YJPayment)
//- (void) setOrderID:(NSString *)orderID {
//    objc_setAssociatedObject(self, &ORDER_KEY, orderID, OBJC_ASSOCIATION_RETAIN);
//}
//
//- (NSString*) orderID {
//    return (NSString *)objc_getAssociatedObject(self, &ORDER_KEY);
//}
//
//- (void) setAmount:(NSNumber*)amount {
//    objc_setAssociatedObject(self, &AMOUNT_KEY, amount, OBJC_ASSOCIATION_RETAIN);
//}
//
//- (NSNumber*) amount {
//    return (NSNumber *)objc_getAssociatedObject(self, &AMOUNT_KEY);
//}
//@end
void _yjAppRequestPayment_impl();

@interface YJAppstoreRechargeObserver : NSObject <SKProductsRequestDelegate,SKPaymentTransactionObserver,SKRequestDelegate>{
}
+ (YJAppstoreRechargeObserver*) sharedRecahrgeObserver;
@property (retain, nonatomic) NSArray* productList;

@end

static YJAppstoreRechargeObserver* g_appstoreRechargeObserver = nil;


@implementation YJAppstoreRechargeObserver

@synthesize productList;

+ (YJAppstoreRechargeObserver*) sharedRecahrgeObserver
{
    @synchronized(self)
    {
        if (nil==g_appstoreRechargeObserver) {
            g_appstoreRechargeObserver = [[YJAppstoreRechargeObserver alloc] init];
        }
    }
    return g_appstoreRechargeObserver;
}

-(id)init
{
    self = [super init];
    if (self) {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    }
    
    return self;
}

-(void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    g_bIsFetchingProducts = false;
    [self setProductList:response.products];
    YJ_POST_NOTIFICATION(YJ_EVENT_APP_PRODUCT_DATA_GOTTEN);
    if (g_startPayment) {
        //** Continue payment
        _yjAppRequestPayment_impl();
    }
}

-(void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions) {
        switch (transaction.transactionState) {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStatePurchasing:
                break;
            case SKPaymentTransactionStateRestored:
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            default:
                
                break;
        }
    }
}

-(void) completeTransaction:(SKPaymentTransaction *)transaction
{
    if (g_bIsFetchingProducts || !g_startPayment) {
        //** Ignore transacation completed before the products informataion received
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
        return;
    }
    g_startPayment = false;
    
    YJAppTransactionReceipt* receipt = new YJAppTransactionReceipt();
    receipt->autorelease();
    receipt->setTransactionReceipt( CCString::createWithData((const unsigned char* )transaction.transactionReceipt.bytes, transaction.transactionReceipt.length) );
    
    receipt->orderID = g_orderID;
    receipt->amount = g_amount;
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    //** Warning!! 这这里之前崩溃会导致漏单
    YJ_POST_NOTIFICATION_WITH_OBJ(YJ_EVENT_APP_TRANSACTION_RECEIPT_GOTTEN, receipt);
}

-(void)failedTransaction:(SKPaymentTransaction *)transaction
{
    if (g_bIsFetchingProducts || !g_startPayment) {
        //** Ignore transacation failed before the products informataion received
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
        return;
    }
    g_startPayment = false;

    YJAppTransactionReceipt* receipt = new YJAppTransactionReceipt();
    receipt->autorelease();
    receipt->orderID = g_orderID;
    receipt->amount = g_amount;
    receipt->setLocalErrorCode(YJAppTransactionReceipt::PAYMENT_CANCELLED);
    if (transaction.error.code != SKErrorPaymentCancelled) {
        NSLog(@"the error is %@",transaction.error.description);
        receipt->setLocalErrorCode(YJAppTransactionReceipt::PAYMENT_ERROR);
        receipt->errorDesc = [transaction.error.localizedDescription UTF8String];
    }
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    YJ_POST_NOTIFICATION_WITH_OBJ(YJ_EVENT_APP_TRANSACTION_RECEIPT_GOTTEN, receipt);
}

@end
void yjAppInit() {
    [YJAppstoreRechargeObserver sharedRecahrgeObserver];
}

void _yjAppRequestPayment_impl()
{
    NSArray* products = [[YJAppstoreRechargeObserver sharedRecahrgeObserver] productList];
    SKProduct* product = nil;
    for (SKProduct *skproduct in products) {
        if ([PRODUCTIDS[g_product_idx] isEqual:skproduct.productIdentifier]) {
            product = skproduct;
            break;
        }
    }
    if (product == nil) {
        g_startPayment = false;
        YJAppTransactionReceipt* receipt = new YJAppTransactionReceipt();
        receipt->autorelease();
        receipt->orderID = g_orderID;
        receipt->amount = g_amount;
        receipt->setLocalErrorCode(YJAppTransactionReceipt::PRODUCT_NOT_FOUND);
        YJ_POST_NOTIFICATION_WITH_OBJ(YJ_EVENT_APP_TRANSACTION_RECEIPT_GOTTEN, receipt);
        return;
    }
    
    SKPayment *payment = nil;
    payment = [SKPayment paymentWithProduct: product];
    NSLog(@"payment  %@",payment);
    [[SKPaymentQueue defaultQueue] addPayment:payment];

}


void yjAppRequestProductData()
{
    g_bIsFetchingProducts = true;
    NSArray* products = nil;
//    if (AppDelegate::isTabletDevice()) {
//        products = [[NSArray alloc] initWithObjects:PRODUCTID_IPAD_1,PRODUCTID_IPAD_2,PRODUCTID_IPAD_3,PRODUCTID_IPAD_4,PRODUCTID_IPAD_5,PRODUCTID_IPAD_6, nil];
//    }
//    else
//        products = [[NSArray alloc] initWithObjects:PRODUCTID_IP_1,PRODUCTID_IP_2,PRODUCTID_IP_3,PRODUCTID_IP_4,PRODUCTID_IP_5,PRODUCTID_IP_6, nil];
    products = [[NSArray alloc] initWithObjects:PRODUCTIDS[0],PRODUCTIDS[1],PRODUCTIDS[2],PRODUCTIDS[3],PRODUCTIDS[4],PRODUCTIDS[5],PRODUCTIDS[6], nil];
    
    NSSet* productsSet = [NSSet setWithArray:products];
    
    SKProductsRequest* request = [[SKProductsRequest alloc] initWithProductIdentifiers:productsSet];
    request.delegate = [YJAppstoreRechargeObserver sharedRecahrgeObserver];
    
    [request start];
    [request release];
    [products release];
}

void yjAppRequestPayment(int productIdx, char* orderID, int amount)
{
    g_startPayment = true;
    g_orderID = orderID;
    g_amount = amount;
    g_product_idx = productIdx;

    NSArray* products = [[YJAppstoreRechargeObserver sharedRecahrgeObserver] productList];
    if (products == nil || [products count]==0) {
        // Request product list
        yjAppRequestProductData();
    }
    else {
        _yjAppRequestPayment_impl();
    }
}

bool yjAppIsProductsEmpty()
{
    return [[YJAppstoreRechargeObserver sharedRecahrgeObserver] productList].count == 0;
}

bool yjAppProductsContainsID(int productIdx)
{
    NSArray* products = [[YJAppstoreRechargeObserver sharedRecahrgeObserver] productList];
    for (SKProduct *skproduct in products) {
        if ([PRODUCTIDS[productIdx] isEqual:skproduct.productIdentifier]) {
            return true;
        }
    }
    
    return false;
}