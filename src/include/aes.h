#ifndef __AES_H__
#define __AES_H__

#include <common.h>
#include <encrypt.h>
#include <decrypt.h>
#include <modes.h>


enum aes_mode{
    CBC,
    CFB,
    OFB,
    CTR,
    ECB
};

void aes_encrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);
void aes_decrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);

#endif // __AES_H__