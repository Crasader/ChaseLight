/*
//  YJCryptor.cpp
//  4399zmxyx
//
//  Created by 439906 on 12-10-24.
//  Copyright (c) 2012年 4399 ios. All rights reserved.
 */

#include "YJCryptor.h"
#include "d3des.h"
#include "ReneBase64.h"

#include <assert.h>
#include <string>
#include <math.h>
#include <zlib.h>

static unsigned int block_size = 8;
#define DES_KEY_LEN 8

void yjDesEncrypt(unsigned char const*  key,
                  unsigned char const*  plaintext,
                  unsigned long         plaintext_len,
                  unsigned char**       p_cryptogram,
                  unsigned long*        cryptogram_len,
                  YJ_DES_OPTION         op)
{
    assert(NULL != key);
    assert(NULL != plaintext);
    assert(NULL != p_cryptogram);
    
    unsigned char key_buf[DES_KEY_LEN];
    memset(key_buf, 0, sizeof(unsigned char)*DES_KEY_LEN);
    memcpy(key_buf, key, DES_KEY_LEN);

    unsigned char padding = 0;
    if (op & YJ_DES_OP_PKCS7_PADDING) {
        // PKCS#7 padding
        padding = block_size - (plaintext_len%block_size);
    }
    unsigned int buffer_len = plaintext_len+padding;
    
    // Buffer input
    unsigned char* in_buf = new unsigned char[buffer_len];
    memset(in_buf, padding, sizeof(unsigned char)*buffer_len);
    memcpy(in_buf, plaintext, plaintext_len);
    
    // Set key for encrypting
    deskey(key_buf, EN0);
    
    // Buffer output
    unsigned char* out_buf = new unsigned char[buffer_len];
    memset(out_buf, 0, sizeof(unsigned char)*buffer_len);
    unsigned int des_cnt = buffer_len / 8;
    
    // Encrypt
    for (int i=0; i!= des_cnt; ++i) {
        des(in_buf + 8*i, out_buf + 8*i);
    }
    delete in_buf;
    
    if (op & YJ_DES_OP_BASE64_PROCESS) {
        std::string str = base64_encode(out_buf, buffer_len);
        buffer_len = str.length();
        delete out_buf;
        out_buf = new unsigned char[buffer_len];
        memset(out_buf, 0, sizeof(unsigned char)*buffer_len);
        memcpy(out_buf, str.c_str(), sizeof(unsigned char)*buffer_len);
    }
    
    *p_cryptogram = out_buf;
    
    if (NULL != cryptogram_len) {
        *cryptogram_len = buffer_len;
    }
}

void yjDesDecrypt(unsigned char const*  key,
                  unsigned char const*  cryptogram,
                  unsigned long         cryptogram_len,
                  unsigned char**       p_plaintext,
                  unsigned long*        plaintext_len,
                  YJ_DES_OPTION         op)
{
    
    assert(NULL != key);
    assert(NULL != cryptogram);
    assert(NULL != p_plaintext);
    
    unsigned char key_buf[DES_KEY_LEN];
    memset(key_buf, 0, sizeof(unsigned char)*DES_KEY_LEN);
    memcpy(key_buf, key, DES_KEY_LEN);
    
    unsigned int buffer_len = cryptogram_len;
    
    // Buffer input
    unsigned char* in_buf = NULL;
    
    if (op & YJ_DES_OP_BASE64_PROCESS) {
        std::string str = base64_decode((const char*)cryptogram);
        buffer_len = str.length();
        in_buf = new unsigned char[buffer_len];
        memset(in_buf, 0, sizeof(unsigned char)*buffer_len);
        memcpy(in_buf, str.c_str(), sizeof(unsigned char)*buffer_len);
    }
    else {
        in_buf = new unsigned char[buffer_len];
        memset(in_buf, 0, sizeof(unsigned char)*buffer_len);
        memcpy(in_buf, cryptogram, sizeof(unsigned char)*buffer_len);
    }
    
    // Set key for descrypting
    deskey(key_buf, DE1);
    
    // Buffer output
    unsigned char* out_buf = new unsigned char[buffer_len];
    memset(out_buf, 0, sizeof(unsigned char)*buffer_len);
    unsigned int des_cnt = buffer_len / 8;
    
    for (int i=0; i!= des_cnt; ++i) {
        des(in_buf + 8*i, out_buf + 8*i);
    }
    delete in_buf;
    
    if (op & YJ_DES_OP_PKCS7_PADDING) {
        // PKCS#7 padding
        int i = buffer_len - 1;
        int padding = out_buf[i];
        if (padding >0 && padding <=8) {
            while (i > 0 && padding-- > 0) {
                out_buf[i] = 0;
                i = --buffer_len - 1;
            }
        }
    }

    *p_plaintext = out_buf;
    
    if (NULL != plaintext_len) {
        *plaintext_len = buffer_len;
    }
}

#define XOR_MASK_LEN (16)
extern void yjXOREncrypt(unsigned char const*   mask,
                         unsigned char const*   plaintext,
                         unsigned long          plaintext_len,
                         unsigned char**        p_cryptogram,
                         unsigned long*         cryptogram_len)
{
    assert(NULL != mask);
    assert(NULL != plaintext);
    assert(NULL != p_cryptogram);
    
    // Length calculation
    unsigned short forhead_padding_len = rand()%17; // 0~16
    unsigned total_len = ceil((float)(10 + forhead_padding_len + plaintext_len)/16)*16;
    unsigned short rear_padding_len = total_len-(10+forhead_padding_len+plaintext_len);
    
    // Buffer output
    unsigned char* buffer_output = new unsigned char[total_len];
    memset(buffer_output, 0, total_len);
    unsigned char* offset = buffer_output;
    
    // Work out CRC
    unsigned long crc32_value = crc32(0, plaintext, plaintext_len);
    
    // Make head
    memcpy(offset, &forhead_padding_len, sizeof(forhead_padding_len));
    offset += sizeof(forhead_padding_len); // should be 2
    memcpy(offset, &plaintext_len, sizeof(plaintext_len));
    offset += sizeof(plaintext_len); // should be 4
    memcpy(offset, &crc32_value, sizeof(crc32_value));
    offset += sizeof(crc32_value); // should be 4
    
    // Make forehead padding
    for (int i=0; i != forhead_padding_len; ++i) {
        *offset++ = rand()%256; // 0~255
    }
        
    // Copy content
    memcpy(offset, plaintext, plaintext_len);
    offset += plaintext_len;
    
    // Make rear padding
    for (int i=0; i != rear_padding_len; ++i) {
        *offset++ = rand()%256; // 0~255
    }
    
#ifdef DEBUG
//    printf("Origin++++++++++++++++++++++++\n");
//    for (int i=0; i != total_len; ++i) {
//        printf("%c", *(buffer_output+i));
//    }
//    printf("\n++++++++++++++++++++++++++++\n");
#endif
    
    // Do xor
#ifdef DEBUG
//    printf("XOR~~~~~~~~~~~~~~~~~~~~~~~~~\n");
#endif
    for (int i=0; i != total_len; ++i) {
        *(buffer_output+i) = (*(buffer_output + i)) ^ *(mask+(i%XOR_MASK_LEN));
#ifdef DEBUG
//        printf("%c", *(buffer_output+i));
#endif
    }
#ifdef DEBUG
//    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
#endif
    
    // Do base64 encoding
    std::string str = base64_encode(buffer_output, total_len);
    total_len = str.length();
    delete [] buffer_output;
    buffer_output = new unsigned char[total_len+8];
    memset(buffer_output, 0, total_len+8);
    memcpy(buffer_output+8, str.c_str(), total_len);
    
#ifdef DEBUG
//    printf("\nBase64-=-=-=-=-=-=-=-=-=-=-=\n");
//    printf("%s",str.c_str());
//    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
#endif
    
    memcpy(buffer_output, "+=4399=+", 8); // XOR flag "+=4399=+"
    
    *p_cryptogram = buffer_output;
    if (NULL != cryptogram_len) {
        *cryptogram_len = total_len+8;
    }
}

extern void yjXORDecrypt(unsigned char const*   mask /* unsigned char[16] */,
                         unsigned char const*   cryptogram,
                         unsigned long          cryptogram_len,
                         unsigned char**        p_plaintext,    /* a new buffer will be set to this pointer */
                         unsigned long*         plaintext_len)
{
    assert(NULL != mask);
    assert(NULL != cryptogram);
    assert(NULL != p_plaintext);
    assert(cryptogram_len >= 8);
    
    std::string flag = std::string((const char*)cryptogram, 8);
    if (flag.compare("+=4399=+") != 0) {
        assert(false);
        return;
    }
    
    // Do base64 decoding
    std::string str = base64_decode(std::string((const char*)cryptogram+8, cryptogram_len-8));
    unsigned long total_len = str.length(); // =cryptogram_len-8
    
    // Buffer input
    unsigned char* buffer_input = new unsigned char[total_len];
    memset(buffer_input, 0, total_len);
    memcpy(buffer_input, str.c_str(), total_len);

    
    // Do xor
    for (int i=0; i != total_len; ++i) {
        *(buffer_input+i) = (*(buffer_input + i)) ^ *(mask+(i%XOR_MASK_LEN));
    }

    // Read head
    unsigned short forhead_padding_len = 0;
    unsigned long content_length = 0;
    unsigned long crc32_value = 0;
    unsigned char* offset = buffer_input;
    memcpy(&forhead_padding_len, offset, sizeof(forhead_padding_len));
    offset += sizeof(forhead_padding_len); // should be 2
    memcpy(&content_length, offset, sizeof(content_length));
    offset += sizeof(content_length); // should be 4
    memcpy(&crc32_value, offset, sizeof(crc32_value));
    offset += sizeof(crc32_value); // should be 4
    
    if (content_length+forhead_padding_len>total_len) {
        assert(false);
        delete [] buffer_input;
        return;
    }
    
    // Ignore forehead padding
    offset += forhead_padding_len;
    
    // Read content
    unsigned char* buffer_output = new unsigned char[content_length];
    memcpy(buffer_output, offset, content_length);
    delete [] buffer_input;
    *p_plaintext = buffer_output;
    
    if (NULL != plaintext_len) {
        *plaintext_len = content_length;
    }
}
