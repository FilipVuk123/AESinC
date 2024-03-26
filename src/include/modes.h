#include <common.h>
#include <encrypt.h>
#include <decrypt.h>

void aes_cbc_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);
void aes_cbc_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

void aes_ctr_xxcrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *nonce, unsigned char *out, int *out_size);

void aes_ofb_xxcrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

void aes_cfb_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);
void aes_cfb_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

void aes_ecb_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *out, int *out_size);
void aes_ecb_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *out, int *out_size);