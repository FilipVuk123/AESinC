#include <aes.h>

void aes_encrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size){
    switch (mode)
    {
    case CBC:
        aes_cbc_encrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    case CFB:
        aes_cfb_encrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    case CTR:
        aes_ctr_xxcrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    case ECB:
        aes_ecb_encrypt(in, in_size, key, key_size, out, out_size);
        break;
    case OFB:
        aes_ofb_xxcrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    
    default:
        break;
    }
}

void aes_decrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size){
    switch (mode)
    {
    case CBC:
        aes_cbc_decrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    case CFB:
        aes_cfb_decrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    case CTR:
        aes_ctr_xxcrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    case ECB:
        aes_ecb_decrypt(in, in_size, key, key_size, out, out_size);
        break;
    case OFB:
        aes_ofb_xxcrypt(in, in_size, key, key_size, iv, out, out_size);
        break;
    
    default:
        break;
    }
}
