#ifndef __AES_H__
#define __AES_H__

#include <common.h>
#include <encrypt.h>
#include <decrypt.h>
#include <modes.h>

enum aes_status{
    SUCCESS,
    ERROR,
    ERROR_INVALID_PARAMETAR,
    ERROR_UNKNOWN_MODE,
    ERROR_UNKNOWN_KEY_SIZE
};

enum aes_mode{
    CBC,
    CFB,
    OFB,
    CTR,
    ECB
};

struct aes_ctx_t{
    unsigned char expanded_key[240]; // expanded key size = AES_BLOCK_SIZE * (n_rounds + 1) ==>> max is: 16 * (14 + 1) = 240
    unsigned char key[SIZE_32]; // max key size
    unsigned char iv[AES_BLOCK_SIZE]; // default iv size
    int expanded_key_size;
    int n_rounds;
    enum aes_mode mode;
    enum aes_key_size size;
};

enum aes_status aes_init(struct aes_ctx_t *ctx, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv);
enum aes_status aes_set_iv(struct aes_ctx_t *ctx, unsigned char* iv);
enum aes_status aes_set_key(struct aes_ctx_t *ctx, unsigned char* key, enum aes_key_size key_size);


enum aes_status aes_encrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int* out_size);
enum aes_status aes_decrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int* out_size);


enum aes_status aes_encrypt_once(unsigned char *in, int in_size, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);
enum aes_status aes_decrypt_once(unsigned char *in, int in_size, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);



#endif // __AES_H__