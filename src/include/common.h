#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AES_BLOCK_SIZE 16

enum aes_key_size{
    SIZE_16 = 16,   // 128
    SIZE_24 = 24,   // 192
    SIZE_32 = 32    // 256
};


int get_nk(enum aes_key_size size);
int get_nr(enum aes_key_size size);

unsigned char get_r_const(unsigned char ch);
unsigned char get_s_box(unsigned char ch);
unsigned char get_rs_box(unsigned char ch);

void key_schedule(unsigned char *word, int iter);
void rotate_word(unsigned char *word);
void rotate_word_inv(unsigned char *word);

void add_round_key(unsigned char *state, unsigned char *round_key);
void key_expansion(unsigned char *expandedKey, unsigned char *key, enum aes_key_size size);
void key_expansion_2(unsigned char *expandedKey, unsigned char *key, enum aes_key_size size, int expandedKeySize);

void create_round_key(unsigned char *expanded_key, unsigned char *round_key);

unsigned char gf_mult(unsigned char a, unsigned char b);

void print_buffer_hex(unsigned char* buffer, int size);

void generate_random_bytes(unsigned char* buffer, int num_bytes);

int equal_buffers(unsigned char* buf1, unsigned char* buf2, int size);

#endif // __COMMON_H__