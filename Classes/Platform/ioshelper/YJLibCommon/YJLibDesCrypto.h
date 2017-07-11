//
//  YJDesCrypto.h
//  zmxy
//
//  Created by yangfeifeng on 7/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface YJLibDesCrypto : NSObject

+(NSString*) decryptUseDES:(NSString*)cipherText key:(NSString*)key;
+(NSString *) encryptUseDES:(NSString *)plainText key:(NSString *)key;
@end
