#ifndef __DECRYPT_H__
#define __DECRYPT_H__


#include <common.h>

void sub_bytes_inv(unsigned char *state);
void shift_rows_inv(unsigned char *state);
void mix_columns_inv(unsigned char *state);

void cipher_inv(unsigned char *state, unsigned char *expanded_key, int n_rounds);

void aes_decrypt_block(unsigned char *input, unsigned char *output, int num_rounds, unsigned char* expanded_key);

#endif // __DECRYPT_H__