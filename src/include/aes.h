#ifndef __AES_H__
#define __AES_H__

#include <common.h>
#include <encrypt.h>
#include <decrypt.h>
#include <modes.h>
#include <timer.h>

/**
 * Enumeration defining various status codes returned by AES functions.
 */
enum aes_status{
    SUCCESS,
    ERROR,
    ERROR_INVALID_PARAMETAR,
    ERROR_UNKNOWN_MODE,
    ERROR_UNKNOWN_KEY_SIZE
};

/**
 * Enumeration defining different encryption modes supported by AES.
 */
enum aes_mode{
    CBC,
    CFB,
    OFB,
    CTR,
    ECB
};

/**
 * Struct representing the context for AES encryption and decryption operations.
 */
struct aes_ctx_t{
    unsigned char expanded_key[240]; // expanded key size = AES_BLOCK_SIZE * (n_rounds + 1) ==>> max is: 16 * (14 + 1) = 240
    unsigned char key[SIZE_32]; // max key size
    unsigned char iv[AES_BLOCK_SIZE]; // default iv size
    int expanded_key_size;
    int n_rounds;
    enum aes_mode mode;
    enum aes_key_size size;
};

/**
 * Initializes the AES context with the provided key, mode, and IV.
 * 
 * @param ctx Pointer to the AES context struct.
 * @param key Encryption key.
 * @param key_size Size of the encryption key.
 * @param mode Encryption mode.
 * @param iv Initialization Vector.
 * @return SUCCESS if initialization is successful, otherwise relevant error code.
 */
enum aes_status aes_init(struct aes_ctx_t *ctx, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv);

/**
 * Sets the Initialization Vector (IV) for AES encryption.
 * 
 * @param ctx Pointer to the AES context struct.
 * @param iv Initialization Vector.
 * @return SUCCESS if IV setting is successful, otherwise relevant error code.
 */
enum aes_status aes_set_iv(struct aes_ctx_t *ctx, unsigned char* iv);

/**
 * Sets the encryption key for AES encryption.
 * 
 * @param ctx Pointer to the AES context struct.
 * @param key Encryption key.
 * @param key_size Size of the encryption key.
 * @return SUCCESS if key setting is successful, otherwise relevant error code.
 */
enum aes_status aes_set_key(struct aes_ctx_t *ctx, unsigned char* key, enum aes_key_size key_size);

/**
 * Encrypts data using AES.
 * 
 * @param ctx Pointer to the AES context struct.
 * @param in Input data to be encrypted.
 * @param in_size Size of the input data.
 * @param out Encrypted output data.
 * @param out_size Pointer to store the size of the encrypted output data.
 * @return SUCCESS if encryption is successful, otherwise relevant error code.
 */
enum aes_status aes_encrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int* out_size);

/**
 * Decrypts data using AES.
 * 
 * @param ctx Pointer to the AES context struct.
 * @param in Encrypted input data to be decrypted.
 * @param in_size Size of the encrypted input data.
 * @param out Decrypted output data.
 * @param out_size Pointer to store the size of the decrypted output data.
 * @return SUCCESS if decryption is successful, otherwise relevant error code.
 */
enum aes_status aes_decrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int* out_size);

/**
 * Encrypts data using AES in a single call.
 * 
 * @param in Input data to be encrypted.
 * @param in_size Size of the input data.
 * @param key Encryption key.
 * @param key_size Size of the encryption key.
 * @param mode Encryption mode.
 * @param iv Initialization Vector.
 * @param out Encrypted output data.
 * @param out_size Pointer to store the size of the encrypted output data.
 * @return SUCCESS if encryption is successful, otherwise relevant error code.
 */
enum aes_status aes_encrypt_once(unsigned char *in, int in_size, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);

/**
 * Decrypts data using AES in a single call.
 * 
 * @param in Encrypted input data to be decrypted.
 * @param in_size Size of the encrypted input data.
 * @param key Encryption key.
 * @param key_size Size of the encryption key.
 * @param mode Encryption mode.
 * @param iv Initialization Vector.
 * @param out Decrypted output data.
 * @param out_size Pointer to store the size of the decrypted output data.
 * @return SUCCESS if decryption is successful, otherwise relevant error code.
 */
enum aes_status aes_decrypt_once(unsigned char *in, int in_size, unsigned char* key, enum aes_key_size key_size, enum aes_mode mode, unsigned char* iv, unsigned char* out, int* out_size);

#endif // __AES_H__
