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
    SIZE_16 = 16,   // 128 bits
    SIZE_24 = 24,   // 192 bits
    SIZE_32 = 32    // 256 bits
};

/**
 * @brief Get the number of key columns based on the AES key size.
 * 
 * @param size The AES key size.
 * @return int The number of key columns.
 */
int get_nk(enum aes_key_size size);

/**
 * @brief Get the number of rounds based on the AES key size.
 * 
 * @param size The AES key size.
 * @return int The number of rounds.
 */
int get_nr(enum aes_key_size size);

/**
 * @brief Get the RCon value based on the given round.
 * 
 * @param ch The round number.
 * @return unsigned char The RCon value.
 */
unsigned char get_r_const(unsigned char ch);

/**
 * @brief Get the value of a byte from the AES S-Box.
 * 
 * @param ch The input byte.
 * @return unsigned char The output byte from the S-Box.
 */
unsigned char get_s_box(unsigned char ch);

/**
 * @brief Get the value of a byte from the AES inverse S-Box.
 * 
 * @param ch The input byte.
 * @return unsigned char The output byte from the inverse S-Box.
 */
unsigned char get_rs_box(unsigned char ch);

/**
 * @brief Perform the key schedule operation.
 * 
 * @param word The word to perform the key schedule on.
 * @param iter The iteration number.
 */
void key_schedule(unsigned char *word, int iter);

/**
 * @brief Rotate the word (4-byte array) left by one byte.
 * 
 * @param word The word to rotate.
 */
void rotate_word(unsigned char *word);

/**
 * @brief Rotate the word (4-byte array) right by one byte.
 * 
 * @param word The word to rotate.
 */
void rotate_word_inv(unsigned char *word);

/**
 * @brief Add the round key to the AES state.
 * 
 * @param state The AES state.
 * @param round_key The round key to add.
 */
void add_round_key(unsigned char *state, unsigned char *round_key);

/**
 * @brief Perform the key expansion operation to expand the initial key.
 * 
 * @param expandedKey The expanded key.
 * @param key The initial key.
 * @param size The size of the key (16, 24, or 32 bytes).
 */
void key_expansion(unsigned char *expandedKey, unsigned char *key, enum aes_key_size size);

/**
 * @brief An alternate key expansion function.
 * 
 * @param expandedKey The expanded key.
 * @param key The initial key.
 * @param size The size of the key (16, 24, or 32 bytes).
 * @param expandedKeySize The size of the expanded key.
 */
void key_expansion_2(unsigned char *expandedKey, unsigned char *key, enum aes_key_size size, int expandedKeySize);

/**
 * @brief Create a round key from the expanded key.
 * 
 * @param expanded_key The expanded key.
 * @param round_key The round key to create.
 */
void create_round_key(unsigned char *expanded_key, unsigned char *round_key);

/**
 * @brief Perform multiplication in the Galois Field (GF).
 * 
 * @param a The first operand.
 * @param b The second operand.
 * @return unsigned char The result of the multiplication.
 */
unsigned char gf_mult(unsigned char a, unsigned char b);

/**
 * @brief Print the contents of a buffer in hexadecimal format.
 * 
 * @param buffer The buffer to print.
 * @param size The size of the buffer.
 */
void print_buffer_hex(unsigned char* buffer, int size);

/**
 * @brief Generate random bytes and fill the buffer.
 * 
 * @param buffer The buffer to fill with random bytes.
 * @param num_bytes The number of bytes to generate.
 */
void generate_random_bytes(unsigned char* buffer, int num_bytes);

/**
 * @brief Check if two buffers are equal.
 * 
 * @param buf1 The first buffer.
 * @param buf2 The second buffer.
 * @param size The size of the buffers.
 * @return int 1 if equal, 0 otherwise.
 */
int equal_buffers(unsigned char* buf1, unsigned char* buf2, int size);

#endif // __COMMON_H__
