#include <modes.h>

static void xor_block(unsigned char *in_1, unsigned char *in_2, int in_size, char *out)
{
    for (int i = 0; i < in_size; ++i)
    {
        out[i] = in_1[i] ^ in_2[i];
    }
}

static void create_PKCS7_buffer(unsigned char* input_buffer, int input_buffer_size, int bytes_to_append, unsigned char* output_buffer) {
    int padded_size = input_buffer_size + bytes_to_append;
    int pad_length = bytes_to_append;

    memcpy(output_buffer, input_buffer, input_buffer_size);

    for (int i = input_buffer_size; i < padded_size; i++) {
        output_buffer[i] = (unsigned char)pad_length;
    }
}

int aes_cbc_encrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size){
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;
    unsigned char padding_buffer[16];

    create_PKCS7_buffer(in + (in_size - modulo), modulo, AES_BLOCK_SIZE - modulo, padding_buffer);
    unsigned char tmp [16];
    
    xor_block(in, iv, AES_BLOCK_SIZE, tmp);
    aes_encrypt_block(tmp, out, key, key_size);
    *out_size = AES_BLOCK_SIZE;
    for(int i = 0; i < num_of_blocks - 1; i++){
        xor_block(out + (i * AES_BLOCK_SIZE), in + ((i + 1) * AES_BLOCK_SIZE), AES_BLOCK_SIZE, tmp);
        aes_encrypt_block(tmp, out + ((i + 1) * AES_BLOCK_SIZE), key, key_size);
        *out_size += AES_BLOCK_SIZE;
    }
    xor_block(out + (num_of_blocks - 1) * AES_BLOCK_SIZE, padding_buffer, AES_BLOCK_SIZE, tmp);
    aes_encrypt_block(tmp, out + num_of_blocks * AES_BLOCK_SIZE, key, key_size);
    *out_size += AES_BLOCK_SIZE;
}

int aes_cbc_decrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size){
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[16];
    
    aes_decrypt_block(in, tmp, key, key_size);
    xor_block(tmp, iv, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;
    
    for(int i = 0; i < num_of_blocks - 1; i++){
        aes_decrypt_block(in + ((i + 1) * AES_BLOCK_SIZE), tmp, key, key_size);
        xor_block(tmp, in + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE, out + ((i + 1) * AES_BLOCK_SIZE));
        *out_size += AES_BLOCK_SIZE;
    }
    *out_size -= out[in_size - 1];
}

int aes_ecb_encrypt(unsigned char* in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* out, int* out_size){
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char padding_buffer[16];

    create_PKCS7_buffer(in + (in_size - modulo), modulo, AES_BLOCK_SIZE - modulo, padding_buffer);
    *out_size = 0;
    for(int i = 0; i < num_of_blocks; i ++){
        aes_encrypt_block(in + (i * AES_BLOCK_SIZE), out + (i * AES_BLOCK_SIZE), key, key_size);
        *out_size += AES_BLOCK_SIZE;
    }
    aes_encrypt_block(padding_buffer, out + (num_of_blocks * AES_BLOCK_SIZE), key, key_size);
    *out_size += AES_BLOCK_SIZE;
}

int aes_ecb_decrypt(unsigned char* in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* out, int* out_size){
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    *out_size = 0;
    for(int i = 0; i < num_of_blocks; i ++){
        aes_decrypt_block(in + (i * AES_BLOCK_SIZE), out + (i * AES_BLOCK_SIZE), key, key_size);
        *out_size += AES_BLOCK_SIZE;
    }
    *out_size -= out[in_size - 1];
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
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;
    unsigned char tmp[AES_BLOCK_SIZE];
    unsigned char nonce_tmp[AES_BLOCK_SIZE];

    memcpy(nonce_tmp, nonce, AES_BLOCK_SIZE);

    aes_encrypt_block(nonce, tmp, key, key_size);
    xor_block(tmp, in, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;

    for(int i = 0; i < num_of_blocks - 1; i++){
        increment_nonce(nonce_tmp);
        aes_encrypt_block(nonce_tmp, tmp, key, key_size);

        xor_block(tmp, in + ((i + 1) * AES_BLOCK_SIZE), AES_BLOCK_SIZE, out + ((i + 1) * AES_BLOCK_SIZE));
        *out_size += AES_BLOCK_SIZE;
    }

    if (modulo > 0){
        increment_nonce(nonce_tmp);
        aes_encrypt_block(nonce_tmp, tmp, key, key_size);
        xor_block(tmp, in + num_of_blocks * AES_BLOCK_SIZE, modulo, out + num_of_blocks * AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}


int aes_cfb_encrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size){
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[AES_BLOCK_SIZE];

    aes_encrypt_block(iv, tmp, key, key_size);
    xor_block(tmp, in, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;
    for (int i = 0; i < num_of_blocks - 1; i++){
        aes_encrypt_block(out + i*AES_BLOCK_SIZE, tmp, key, key_size);
        xor_block(tmp, in + (i + 1)*AES_BLOCK_SIZE, AES_BLOCK_SIZE, out + (i + 1)*AES_BLOCK_SIZE);
        *out_size += AES_BLOCK_SIZE;
    }

    if (modulo > 0){
        aes_encrypt_block(out + (num_of_blocks - 1)*AES_BLOCK_SIZE, tmp, key, key_size);
        xor_block(tmp, in + num_of_blocks*AES_BLOCK_SIZE, modulo, out + num_of_blocks*AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}

int aes_cfb_decrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size){
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[AES_BLOCK_SIZE];

    aes_encrypt_block(iv, tmp, key, key_size);
    xor_block(tmp, in, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;

    for (int i = 0; i < num_of_blocks - 1; i++){
        aes_encrypt_block(in + i*AES_BLOCK_SIZE, tmp, key, key_size);
        xor_block(tmp, in + (i + 1)*AES_BLOCK_SIZE, AES_BLOCK_SIZE, out + (i + 1)*AES_BLOCK_SIZE);
        *out_size += AES_BLOCK_SIZE;
    }

    if (modulo > 0){
        aes_encrypt_block(in + (num_of_blocks - 1)*AES_BLOCK_SIZE, tmp, key, key_size);
        xor_block(tmp, in + num_of_blocks*AES_BLOCK_SIZE, modulo, out + num_of_blocks*AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}



int aes_ofb_xxcrypt(unsigned char *in, int in_size, unsigned char* key, enum key_size key_size, unsigned char* iv, unsigned char* out, int* out_size){
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[AES_BLOCK_SIZE];

    aes_encrypt_block(iv, tmp, key, key_size);
    xor_block(in, tmp, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;

    for(int i = 0; i < num_of_blocks - 1; i++){
        aes_encrypt_block(tmp, tmp, key, key_size);
        xor_block(in + (i + 1)*AES_BLOCK_SIZE, tmp, AES_BLOCK_SIZE, out + (i + 1)*AES_BLOCK_SIZE);
        *out_size += AES_BLOCK_SIZE;
    }
    
    if (modulo > 0){
        aes_encrypt_block(tmp, tmp, key, key_size);
        xor_block(in + num_of_blocks*AES_BLOCK_SIZE, tmp, modulo, out + num_of_blocks*AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}