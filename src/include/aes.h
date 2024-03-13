#ifndef __AES_H__
#define __AES_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum keySize{
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

void sub_bytes(unsigned char *state);
void shift_rows(unsigned char *state);
void mix_columns(unsigned char *state);
void sub_bytes_inv(unsigned char *state);
void shift_rows_inv(unsigned char *state);
void mix_columns_inv(unsigned char *state);

void add_round_key(unsigned char *state, unsigned char *round_key);
void key_expansion(unsigned char *expandedKey, unsigned char *key, enum keySize size);
void key_expansion_2(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize);

void aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
void aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);


#endif // __AES_H__