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

struct aes_ctx_t{
    int expanded_key_size;
    int n_rounds;
    enum aes_mode mode;
    enum aes_key_size size;
    unsigned char* key;
    unsigned char* iv;
    unsigned char* expanded_key;
};

void aes_encrypt_once(unsigned char *in, int in_size, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);
void aes_decrypt_once(unsigned char *in, int in_size, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);



void aes_init(struct aes_ctx_t *ctx, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv);
void aes_set_iv(struct aes_ctx_t *ctx, unsigned char* iv);

void aes_encrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int* out_size);
void aes_decrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int* out_size);

void aes_destroy(struct aes_ctx_t *ctx);

#endif // __AES_H__