/*
//  YJCryptor.h
//  4399zmxyx
//
//  Created by 439906 on 12-10-24.
//  Copyright (c) 2012年 4399 ios. All rights reserved.
 */

#ifndef ___399zmxyx__YJCryptor__
#define ___399zmxyx__YJCryptor__

#include <stdlib.h>

/*
 *  DES Cryptor
 *
 */
enum {
    YJ_DES_OP_EBC,
    YJ_DES_OP_CBC,                     //** Not support yet
    YJ_DES_OP_NO_PADDING = 0x10,
    YJ_DES_OP_PKCS7_PADDING = 0x20,    //** Since the block size is 8, so PKCS7 does the same effect as PKCS5 here
    YJ_DES_OP_BASE64_PROCESS = 0x100,
};
typedef int YJ_DES_OPTION;

extern void yjDesEncrypt(unsigned char const*   key   /* unsigned char[8] */,
                         unsigned char const*   plaintext,
                         unsigned long          plaintext_len,
                         unsigned char**        p_cryptogram,   /* a new buffer will be set to this pointer */
                         unsigned long*         cryptogram_len = NULL,
                         YJ_DES_OPTION          op = YJ_DES_OP_EBC|YJ_DES_OP_PKCS7_PADDING|YJ_DES_OP_BASE64_PROCESS);

extern void yjDesDecrypt(unsigned char const*   key   /* unsigned char[8] */,
                         unsigned char const*   cryptogram,
                         unsigned long          cryptogram_len,
                         unsigned char**        p_plaintext,    /* a new buffer will be set to this pointer */
                         unsigned long*         plaintext_len = NULL,
                         YJ_DES_OPTION          op = YJ_DES_OP_EBC|YJ_DES_OP_PKCS7_PADDING|YJ_DES_OP_BASE64_PROCESS);



/*
 * YJ XOR Cryptor
 *
 */

extern void yjXOREncrypt(unsigned char const*   key /* unsigned char[16] */,
                         unsigned char const*   plaintext,
                         unsigned long          plaintext_len,
                         unsigned char**        p_cryptogram,   /* a new buffer will be set to this pointer */
                         unsigned long*         cryptogram_len = NULL);

extern void yjXORDecrypt(unsigned char const*   key /* unsigned char[16] */,
                         unsigned char const*   cryptogram,
                         unsigned long          cryptogram_len,
                         unsigned char**        p_plaintext,    /* a new buffer will be set to this pointer */
                         unsigned long*         plaintext_len = NULL);

#endif /* defined(___399zmxyx__YJCryptor__) */
