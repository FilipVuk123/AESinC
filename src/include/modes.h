#include <common.h>
#include <encrypt.h>
#include <decrypt.h>


int aes_cbc_encrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size);
int aes_cbc_decrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size);

int aes_ctr_xxcrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* nonce, unsigned char* out, int* out_size);

int aes_ofb_xxcrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size);

int aes_cfb_encrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size);
int aes_cfb_decrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size);


int aes_ecb_encrypt(unsigned char* in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* out, int* out_size);
int aes_ecb_decrypt(unsigned char* in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* out, int* out_size);