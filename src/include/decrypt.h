#ifndef __DECRYPT_H__
#define __DECRYPT_H__

#include <common.h>

/**
 * @brief Perform the inverse SubBytes operation on the AES state.
 * 
 * @param state The AES state.
 */
void sub_bytes_inv(unsigned char *state);

/**
 * @brief Perform the inverse ShiftRows operation on the AES state.
 * 
 * @param state The AES state.
 */
void shift_rows_inv(unsigned char *state);

/**
 * @brief Perform the inverse MixColumns operation on the AES state.
 * 
 * @param state The AES state.
 */
void mix_columns_inv(unsigned char *state);

/**
 * @brief Perform AES decryption on a single block.
 * 
 * @param input The input block to decrypt.
 * @param output The output block to store the decrypted data.
 * @param num_rounds The number of rounds in AES encryption.
 * @param expanded_key The expanded key.
 */
void aes_decrypt_block(unsigned char *input, unsigned char *output, int num_rounds, unsigned char* expanded_key);

#endif // __DECRYPT_H__
