#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#include <common.h>

/**
 * @brief Perform the SubBytes operation on the AES state.
 * 
 * @param state The AES state.
 */
void sub_bytes(unsigned char *state);

/**
 * @brief Perform the ShiftRows operation on the AES state.
 * 
 * @param state The AES state.
 */
void shift_rows(unsigned char *state);

/**
 * @brief Perform the MixColumns operation on the AES state.
 * 
 * @param state The AES state.
 */
void mix_columns(unsigned char *state);

/**
 * @brief Perform AES encryption on a single block.
 * 
 * @param input The input block to encrypt.
 * @param output The output block to store the encrypted data.
 * @param num_rounds The number of rounds in AES encryption.
 * @param expanded_key The expanded key.
 */
void aes_encrypt_block(unsigned char *input, unsigned char *output, int num_rounds, unsigned char* expanded_key);

#endif // __ENCRYPT_H__
