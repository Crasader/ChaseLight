//
//  YJAppstoreHelper.h
//  4399zmxyx
//
//  Created by longyan on 13-12-11.
//  Copyright (c) 2013年 4399 ios. All rights reserved.
//

#ifndef ___399zmxyx__YJAppstoreHelper__
#define ___399zmxyx__YJAppstoreHelper__

#include "cocos2d.h"
#include "ReneBase64.h"
#include "YJJSONParser.h"

USING_NS_CC;

class YJAppTransactionReceipt :public cocos2d::CCNode, public YJSerializableObj {
public:
    enum LOCAL_ERROR {
        OK,
        PRODUCT_NOT_FOUND = 1,
        PAYMENT_CANCELLED,
        PAYMENT_ERROR,
    };
public:
    std::string orderID;
    unsigned int amount;
    std::string errorDesc;
    
    CC_SYNTHESIZE_RETAIN(CCString*, transactionReceipt, TransactionReceipt);
    CC_SYNTHESIZE(int, localErrorCode, LocalErrorCode);
    
public:
    YJAppTransactionReceipt(): transactionReceipt(NULL),amount(0),localErrorCode(OK){}
    
    virtual ~YJAppTransactionReceipt(){
        CC_SAFE_RELEASE_NULL(transactionReceipt);
    }
    
    std::string getBase64Receipt() {
        return base64_encode((unsigned char const*)(transactionReceipt->getCString()), transactionReceipt->length());
    }
    
    void setOrderID(const char* order_id) {
        orderID = order_id;
    }
    
    //-- implement YJSerializableObj
    virtual JsonCpp::Value serializedJsonValue() {
        JsonCpp::Value ret = YJSerializableObj::serializedJsonValue();
        
        ret["receipt"] = transactionReceipt->getCString();
        ret["orderID"] = orderID;
        ret["amount"] = amount;
        
        return ret;
    };
    
    virtual bool deserializeFromJsonValue(const JsonCpp::Value& value){
        if( !isValidData(value) ){
            return false;
        }
        
        transactionReceipt = CCString::create( value["receipt"].asCString() );
        CC_SAFE_RETAIN(transactionReceipt);
        orderID = value["orderID"].asString();
        amount = getIntValueFromJson( value["amount"] );
        
        return true;
    };
    
    virtual bool isValidData(const JsonCpp::Value& value){
        if (!value.isMember("receipt")) {
            return false;
        }
        if (!value.isMember("orderID")) {
            return false;
        }
        if (!value.isMember("amount")) {
            return false;
        }
        
        return true;
    };
};

extern void yjAppInit();
extern void yjAppRequestProductData();
extern void yjAppRequestPayment(int productIdx, char* orderID, int amount);
extern bool yjAppIsProductsEmpty();
extern bool yjAppProductsContainsID(int productIdx);

#endif /* defined(___399zmxyx__YJAppstoreHelper__) */
