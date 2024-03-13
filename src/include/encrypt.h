#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#include <common.h>

void sub_bytes(unsigned char *state);
void shift_rows(unsigned char *state);
void mix_columns(unsigned char *state);

void cipher(unsigned char *state, unsigned char *expanded_key, int n_rounds);

void aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum key_size size);

#endif // __ENCRYPT_H__