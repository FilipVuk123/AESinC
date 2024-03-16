#include <modes.h>

static void xor_block(unsigned char *in_1, unsigned char *in_2, int in_size, char *out)
{
    for (int i = 0; i < in_size; ++i)
    {
        out[i] = in_1[i] ^ in_2[i];
    }
}

int aes_cbc_encrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size){
    unsigned char tmp [16];
    xor_block(in, iv, AES_BLOCK_SIZE, tmp);
    aes_encrypt_block(tmp, out, key, key_size);
    

    // xor_block(out, in + AES_BLOCK_SIZE, AES_BLOCK_SIZE, tmp);
    // aes_encrypt_block(tmp, out + AES_BLOCK_SIZE, key, key_size);
    
    // xor_block(out + AES_BLOCK_SIZE, in + 2 * AES_BLOCK_SIZE, AES_BLOCK_SIZE, tmp);
    // aes_encrypt_block(tmp, out + 2 * AES_BLOCK_SIZE, key, key_size);
    
    for(int i = 0; i < in_size / AES_BLOCK_SIZE - 1; i++){
        xor_block(out + (i * AES_BLOCK_SIZE), in + ((i + 1) * AES_BLOCK_SIZE), AES_BLOCK_SIZE, tmp);
        aes_encrypt_block(tmp, out + ((i + 1) * AES_BLOCK_SIZE), key, key_size);
    }
}


int aes_cbc_decrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size){
    unsigned char tmp[16];
    aes_decrypt_block(in, tmp, key, key_size);
    xor_block(tmp, iv, AES_BLOCK_SIZE, out);
    
    for(int i = 0; i < in_size / AES_BLOCK_SIZE - 1; i++){
        aes_decrypt_block(in + ((i + 1) * AES_BLOCK_SIZE), tmp, key, key_size);
        xor_block(tmp, in + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE, out + ((i + 1) * AES_BLOCK_SIZE));
    }
    // aes_decrypt_block(in + AES_BLOCK_SIZE, tmp, key, key_size);
    // xor_block(tmp, in, AES_BLOCK_SIZE, out + AES_BLOCK_SIZE);

    // aes_decrypt_block(in + 2 * AES_BLOCK_SIZE, tmp, key, key_size);
    // xor_block(tmp, in + AES_BLOCK_SIZE, AES_BLOCK_SIZE, out + 2 * AES_BLOCK_SIZE);
}


static void increment_nonce(unsigned char *nonce) {
    int i;
    for (i = AES_BLOCK_SIZE - 1; i >= 0; i--) {
        nonce[i]++;
        if (nonce[i] != 0) {
            break; 
        }
    }
    if (i < 0) {
        memset(nonce, 0, AES_BLOCK_SIZE);
    }
}

int aes_ctr_xxcrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* nonce, unsigned char* out, int* out_size){
    unsigned char tmp[16];
    unsigned char nonce_tmp[16];

    memcpy(nonce_tmp, nonce, AES_BLOCK_SIZE);

    aes_encrypt_block(nonce, tmp, key, key_size);
    xor_block(tmp, in, AES_BLOCK_SIZE, out);

    printBufferHex(nonce_tmp, 16);

    for(int i = 0; i < in_size / AES_BLOCK_SIZE - 1; i++){
        increment_nonce(nonce_tmp);
        printBufferHex(nonce_tmp, 16);
        aes_encrypt_block(nonce_tmp, tmp, key, key_size);

        xor_block(tmp, in + ((i + 1) * AES_BLOCK_SIZE), AES_BLOCK_SIZE, out + ((i + 1) * AES_BLOCK_SIZE));
    }

    // increment_nonce(nonce_tmp);

    // aes_encrypt_block(nonce_tmp, tmp, key, key_size);
    // xor_block(tmp, in + AES_BLOCK_SIZE, AES_BLOCK_SIZE, out+ AES_BLOCK_SIZE);

    // increment_nonce(nonce_tmp);

    // aes_encrypt_block(nonce_tmp, tmp, key, key_size);
    // xor_block(tmp, in + 2*AES_BLOCK_SIZE, AES_BLOCK_SIZE, out+ 2*AES_BLOCK_SIZE);

    // increment_nonce(nonce_tmp);

    // aes_encrypt_block(nonce_tmp, tmp, key, key_size);
    // xor_block(tmp, in + 3*AES_BLOCK_SIZE, AES_BLOCK_SIZE, out+ 3*AES_BLOCK_SIZE);
}


int aes_ecb_encrypt(unsigned char* in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* out, int* out_size){
    for(int i = 0; i < in_size / AES_BLOCK_SIZE; i ++){
        aes_encrypt_block(in + (i * AES_BLOCK_SIZE), out + (i * AES_BLOCK_SIZE), key, key_size);
    }
}


int aes_ecb_decrypt(unsigned char* in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* out, int* out_size){
    for(int i = 0; i < in_size / AES_BLOCK_SIZE; i ++){
        aes_decrypt_block(in + (i * AES_BLOCK_SIZE), out + (i * AES_BLOCK_SIZE), key, key_size);
    }
}