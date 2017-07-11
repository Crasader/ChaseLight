//
//  YJDesCrypto.m
//  zmxy
//
//  Created by yangfeifeng on 7/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "YJLibDesCrypto.h"
#import <CommonCrypto/CommonCryptor.h>
#import "YJLibGTMBase64.h"

@implementation YJLibDesCrypto

+(NSString*) decryptUseDES:(NSString*)cipherText key:(NSString*)key 
{  
    NSData* cipherData = [YJLibGTMBase64 decodeString:cipherText];  
    unsigned char buffer[1024];  
    memset(buffer, 0, sizeof(char));  
    size_t numBytesDecrypted = 0;  
    CCCryptorStatus cryptStatus = CCCrypt(kCCDecrypt,   
                                          kCCAlgorithmDES,   
                                          kCCOptionPKCS7Padding,   
                                          [key UTF8String],   
                                          kCCKeySizeDES,   
                                          NULL,   
                                          [cipherData bytes],   
                                          [cipherData length],   
                                          buffer,   
                                          1024,   
                                          &numBytesDecrypted);  
    NSString* plainText = nil;  
    if (cryptStatus == kCCSuccess) {  
        NSData* data = [NSData dataWithBytes:buffer length:(NSUInteger)numBytesDecrypted];  
        plainText = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];  
    }  
    return plainText;  
}  

+(NSString *) encryptUseDES:(NSString *)plainText key:(NSString *)key
{
    NSString *ciphertext = nil;
    const char *textBytes = [plainText UTF8String];
    NSUInteger dataLength = [plainText length];
    unsigned char buffer[1024];
    memset(buffer, 0, sizeof(char));
    size_t numBytesEncrypted = 0;
    CCCryptorStatus cryptStatus = CCCrypt(kCCEncrypt, kCCAlgorithmDES,
                                          kCCOptionPKCS7Padding,
                                          [key UTF8String], kCCKeySizeDES,
                                          NULL,
                                          textBytes, dataLength,
                                          buffer, 1024,
                                          &numBytesEncrypted);
    if (cryptStatus == kCCSuccess) {
        NSData *data = [NSData dataWithBytes:buffer length:(NSUInteger)numBytesEncrypted];
   
        ciphertext = [[[NSString alloc] initWithData:[YJLibGTMBase64 encodeData:data] encoding:NSUTF8StringEncoding] autorelease];
    }
    
    return ciphertext;
}
@end
