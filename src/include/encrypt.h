#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#include <common.h>

void sub_bytes(unsigned char *state);
void shift_rows(unsigned char *state);
void mix_columns(unsigned char *state);

void cipher(unsigned char *state, unsigned char *expanded_key, int n_rounds);

void aes_encrypt_block(unsigned char *input, unsigned char *output, int num_rounds, unsigned char* expanded_key);

#endif // __ENCRYPT_H__