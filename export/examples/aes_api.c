#include <aes.h>
#include <stdio.h>

// This example shows how to use aes api for encryption. For decryption it would look like the same with aes_decrypt funtions

int main()
{

    unsigned char key[16];
    generate_random_bytes(key, 16);
    printf("\Key (HEX format):\n");
    print_buffer_hex(key, 16);

    unsigned char key2[32];
    generate_random_bytes(key2, 32);
    printf("\Key2 (HEX format):\n");
    print_buffer_hex(key2, 32);

    unsigned char iv1[16];
    generate_random_bytes(iv1, 16);
    printf("\Iv1 (HEX format):\n");
    print_buffer_hex(iv1, 16);

    unsigned char iv2[16];
    generate_random_bytes(iv2, 16);
    printf("\Iv2 (HEX format):\n");
    print_buffer_hex(iv2, 16);


    unsigned char plaintext1[] = {"testing the aes api example with multiple ivs and keys to show how it would work"};
    unsigned char plaintext2[] = {"abcdef1123456789  0filip123321a|bcdeabcd  ef1234567890fil??ip123321a{]}  bcde!!!"};
    int plaintext1_size = strlen(plaintext1);
    int plaintext2_size = strlen(plaintext2);
    int outsize;

    unsigned char ciphertext1[plaintext1_size + AES_BLOCK_SIZE];
    unsigned char ciphertext2[plaintext2_size + AES_BLOCK_SIZE];

    printf("\nPlaintext (HEX format):\n");
    print_buffer_hex(plaintext1, plaintext1_size);

    // lets initialize an aes context

    struct aes_ctx_t aes_encrypt_ctx;
    aes_init(&aes_encrypt_ctx, key, SIZE_32, CBC, iv1);
    aes_encrypt(&aes_encrypt_ctx, plaintext1, plaintext1_size, ciphertext1, &outsize);
    printf("\nCiphertext (HEX format):\n");
    print_buffer_hex(ciphertext1, outsize);

    aes_set_iv(&aes_encrypt_ctx, iv2);
    aes_encrypt(&aes_encrypt_ctx, plaintext1, plaintext1_size, ciphertext1, &outsize);
    printf("\nCiphertext (HEX format):\n");
    print_buffer_hex(ciphertext1, outsize);

    aes_set_key(&aes_encrypt_ctx, key2, SIZE_32);
    aes_set_iv(&aes_encrypt_ctx, iv1);
    aes_encrypt(&aes_encrypt_ctx, plaintext2, plaintext2_size, ciphertext2, &outsize);
    printf("\nCiphertext (HEX format):\n");
    print_buffer_hex(ciphertext2, outsize);

    aes_set_iv(&aes_encrypt_ctx, iv2);
    aes_encrypt(&aes_encrypt_ctx, plaintext2, plaintext2_size, ciphertext2, &outsize);
    printf("\nCiphertext (HEX format):\n");
    print_buffer_hex(ciphertext2, outsize);


    printf("\nExiting...\n\n");
    return 0;
}