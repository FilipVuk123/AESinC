#include <modes.h>

/**
 * @brief XOR operation between two blocks of data.
 *
 * @param in_1 The first input block.
 * @param in_2 The second input block.
 * @param in_size The size of the input blocks.
 * @param out The output block.
 */
static void xor_blocks(unsigned char *in_1, unsigned char *in_2, int in_size, unsigned char *out)
{
    for (int i = 0; i < in_size; ++i)
    {
        out[i] = in_1[i] ^ in_2[i];
    }
}

/**
 * @brief XOR operation between a block of data and a repeating chunk of data.
 *
 * @param block The input block.
 * @param block_size The size of the input block.
 * @param chunk The repeating chunk.
 * @param chunk_size The size of the repeating chunk.
 * @param out The output block.
 */
static void xor_block_by_chunk(unsigned char *block, int block_size, unsigned char *chunk, int chunk_size, unsigned char *out)
{
    for (int i = 0; i < block_size; ++i)
    {
        out[i] = block[i] ^ chunk[i % chunk_size];
    }
}

/**
 * @brief Create a PKCS7 padding buffer for the input buffer.
 *
 * @param input_buffer The input buffer.
 * @param input_buffer_size The size of the input buffer.
 * @param bytes_to_append The number of bytes to append for padding.
 * @param output_buffer The output buffer with PKCS7 padding.
 */
static void create_PKCS7_buffer(unsigned char *input_buffer, int input_buffer_size, int bytes_to_append, unsigned char *output_buffer)
{
    int padded_size = input_buffer_size + bytes_to_append;
    int pad_length = bytes_to_append;

    memcpy(output_buffer, input_buffer, input_buffer_size);

    for (int i = input_buffer_size; i < padded_size; i++)
    {
        output_buffer[i] = (unsigned char)pad_length;
    }
}

void aes_cbc_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    *out_size = 0;

    unsigned char padding_buffer[AES_BLOCK_SIZE];

    create_PKCS7_buffer(in + (in_size - modulo), modulo, AES_BLOCK_SIZE - modulo, padding_buffer);
    unsigned char tmp[AES_BLOCK_SIZE];

    if (in_size < AES_BLOCK_SIZE)
    {
        xor_blocks(padding_buffer, iv, AES_BLOCK_SIZE, tmp);
        aes_encrypt_block(tmp, out, n_rounds, expanded_key);
        *out_size += AES_BLOCK_SIZE;
        return;
    }

    xor_blocks(in, iv, AES_BLOCK_SIZE, tmp);
    aes_encrypt_block(tmp, out, n_rounds, expanded_key);
    *out_size += AES_BLOCK_SIZE;
    for (int i = 0; i < num_of_blocks - 1; i++)
    {
        xor_blocks(out + (i * AES_BLOCK_SIZE), in + ((i + 1) * AES_BLOCK_SIZE), AES_BLOCK_SIZE, tmp);
        aes_encrypt_block(tmp, out + ((i + 1) * AES_BLOCK_SIZE), n_rounds, expanded_key);
        *out_size += AES_BLOCK_SIZE;
    }
    xor_blocks(out + (num_of_blocks - 1) * AES_BLOCK_SIZE, padding_buffer, AES_BLOCK_SIZE, tmp);
    aes_encrypt_block(tmp, out + num_of_blocks * AES_BLOCK_SIZE, n_rounds, expanded_key);
    *out_size += AES_BLOCK_SIZE;
}

void aes_cbc_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;

    *out_size = 0;

    unsigned char tmp[AES_BLOCK_SIZE];

    aes_decrypt_block(in, tmp, n_rounds, expanded_key);
    xor_blocks(tmp, iv, AES_BLOCK_SIZE, out);
    *out_size += AES_BLOCK_SIZE;

    for (int i = 0; i < num_of_blocks - 1; i++)
    {
        aes_decrypt_block(in + ((i + 1) * AES_BLOCK_SIZE), tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in + (i * AES_BLOCK_SIZE), AES_BLOCK_SIZE, out + ((i + 1) * AES_BLOCK_SIZE));
        *out_size += AES_BLOCK_SIZE;
    }
    *out_size -= out[in_size - 1];
}

void aes_ecb_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char padding_buffer[AES_BLOCK_SIZE];

    create_PKCS7_buffer(in + (in_size - modulo), modulo, AES_BLOCK_SIZE - modulo, padding_buffer);
    *out_size = 0;
    for (int i = 0; i < num_of_blocks; i++)
    {
        aes_encrypt_block(in + (i * AES_BLOCK_SIZE), out + (i * AES_BLOCK_SIZE), n_rounds, expanded_key);
        *out_size += AES_BLOCK_SIZE;
    }
    aes_encrypt_block(padding_buffer, out + (num_of_blocks * AES_BLOCK_SIZE), n_rounds, expanded_key);
    *out_size += AES_BLOCK_SIZE;
}

void aes_ecb_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;

    *out_size = 0;
    for (int i = 0; i < num_of_blocks; i++)
    {
        aes_decrypt_block(in + (i * AES_BLOCK_SIZE), out + (i * AES_BLOCK_SIZE), n_rounds, expanded_key);
        *out_size += AES_BLOCK_SIZE;
    }
    *out_size -= out[in_size - 1];
}

static void increment_nonce(unsigned char *nonce)
{
    int i;
    for (i = AES_BLOCK_SIZE - 1; i >= 0; i--)
    {
        nonce[i]++;
        if (nonce[i] != 0)
        {
            break;
        }
    }
    if (i < 0)
    {
        memset(nonce, 0, AES_BLOCK_SIZE);
    }
}

void aes_ctr_xxcrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *nonce, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[AES_BLOCK_SIZE];
    unsigned char nonce_tmp[AES_BLOCK_SIZE];

    *out_size = 0;

    memcpy(nonce_tmp, nonce, AES_BLOCK_SIZE);

    if (in_size < AES_BLOCK_SIZE)
    {
        aes_encrypt_block(nonce_tmp, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in + num_of_blocks * AES_BLOCK_SIZE, modulo, out + num_of_blocks * AES_BLOCK_SIZE);
        *out_size += modulo;
        return;
    }

    aes_encrypt_block(nonce, tmp, n_rounds, expanded_key);
    xor_blocks(tmp, in, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;

    for (int i = 0; i < num_of_blocks - 1; i++)
    {
        increment_nonce(nonce_tmp);
        aes_encrypt_block(nonce_tmp, tmp, n_rounds, expanded_key);

        xor_blocks(tmp, in + ((i + 1) * AES_BLOCK_SIZE), AES_BLOCK_SIZE, out + ((i + 1) * AES_BLOCK_SIZE));
        *out_size += AES_BLOCK_SIZE;
    }

    if (modulo > 0)
    {
        increment_nonce(nonce_tmp);
        aes_encrypt_block(nonce_tmp, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in + num_of_blocks * AES_BLOCK_SIZE, modulo, out + num_of_blocks * AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}

void aes_cfb_encrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[AES_BLOCK_SIZE];

    *out_size = 0;

    if (in_size < AES_BLOCK_SIZE)
    {
        aes_encrypt_block(iv, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in, modulo, out);
        *out_size += modulo;
        return;
    }

    aes_encrypt_block(iv, tmp, n_rounds, expanded_key);
    xor_blocks(tmp, in, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;
    for (int i = 0; i < num_of_blocks - 1; i++)
    {
        aes_encrypt_block(out + i * AES_BLOCK_SIZE, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in + (i + 1) * AES_BLOCK_SIZE, AES_BLOCK_SIZE, out + (i + 1) * AES_BLOCK_SIZE);
        *out_size += AES_BLOCK_SIZE;
    }

    if (modulo > 0)
    {
        aes_encrypt_block(out + (num_of_blocks - 1) * AES_BLOCK_SIZE, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in + num_of_blocks * AES_BLOCK_SIZE, modulo, out + num_of_blocks * AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}

void aes_cfb_decrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[AES_BLOCK_SIZE];

    *out_size = 0;

    if (in_size < AES_BLOCK_SIZE)
    {
        aes_encrypt_block(iv, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in, modulo, out);
        *out_size += modulo;
        return;
    }

    aes_encrypt_block(iv, tmp, n_rounds, expanded_key);
    xor_blocks(tmp, in, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;

    for (int i = 0; i < num_of_blocks - 1; i++)
    {
        aes_encrypt_block(in + i * AES_BLOCK_SIZE, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in + (i + 1) * AES_BLOCK_SIZE, AES_BLOCK_SIZE, out + (i + 1) * AES_BLOCK_SIZE);
        *out_size += AES_BLOCK_SIZE;
    }

    if (modulo > 0)
    {
        aes_encrypt_block(in + (num_of_blocks - 1) * AES_BLOCK_SIZE, tmp, n_rounds, expanded_key);
        xor_blocks(tmp, in + num_of_blocks * AES_BLOCK_SIZE, modulo, out + num_of_blocks * AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}

void aes_ofb_xxcrypt(unsigned char *in, int in_size, unsigned char *expanded_key, int n_rounds, unsigned char *iv, unsigned char *out, int *out_size)
{
    int num_of_blocks = in_size / AES_BLOCK_SIZE;
    int modulo = in_size % AES_BLOCK_SIZE;

    unsigned char tmp[AES_BLOCK_SIZE];

    *out_size = 0;
    if (in_size < AES_BLOCK_SIZE)
    {
        aes_encrypt_block(iv, tmp, n_rounds, expanded_key);
        xor_blocks(in, tmp, modulo, out);
        *out_size += modulo;
        return;
    }

    aes_encrypt_block(iv, tmp, n_rounds, expanded_key);
    xor_blocks(in, tmp, AES_BLOCK_SIZE, out);
    *out_size = AES_BLOCK_SIZE;

    for (int i = 0; i < num_of_blocks - 1; i++)
    {
        aes_encrypt_block(tmp, tmp, n_rounds, expanded_key);
        xor_blocks(in + (i + 1) * AES_BLOCK_SIZE, tmp, AES_BLOCK_SIZE, out + (i + 1) * AES_BLOCK_SIZE);
        *out_size += AES_BLOCK_SIZE;
    }

    if (modulo > 0)
    {
        aes_encrypt_block(tmp, tmp, n_rounds, expanded_key);
        xor_blocks(in + num_of_blocks * AES_BLOCK_SIZE, tmp, modulo, out + num_of_blocks * AES_BLOCK_SIZE);
        *out_size += modulo;
    }
}