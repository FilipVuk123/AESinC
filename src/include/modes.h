#include <common.h>
#include <encrypt.h>
#include <decrypt.h>

/**
 * @brief Perform AES-CBC encryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param iv The initialization vector.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_cbc_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

/**
 * @brief Perform AES-CBC decryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param iv The initialization vector.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_cbc_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

/**
 * @brief Perform AES-CTR encryption or decryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param nonce The nonce value.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_ctr_xxcrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *nonce, unsigned char *out, int *out_size);

/**
 * @brief Perform AES-OFB encryption or decryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param iv The initialization vector.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_ofb_xxcrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

/**
 * @brief Perform AES-CFB encryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param iv The initialization vector.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_cfb_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

/**
 * @brief Perform AES-CFB decryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param iv The initialization vector.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_cfb_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size);

/**
 * @brief Perform AES-ECB encryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_ecb_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *out, int *out_size);

/**
 * @brief Perform AES-ECB decryption.
 * 
 * @param in The input data.
 * @param in_size The size of the input data.
 * @param expanded_key The expanded AES key.
 * @param n_rounds The number of AES rounds.
 * @param out The output data.
 * @param out_size The size of the output data.
 */
void aes_ecb_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *out, int *out_size);
