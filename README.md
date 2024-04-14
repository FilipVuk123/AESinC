# AES Implementation with Standard Modes of Operation

This project provides a complete implementation of the Advanced Encryption Standard (AES) algorithm along with five standard modes of operation: CBC (Cipher Block Chaining), ECB (Electronic Codebook), CTR (Counter), CFB (Cipher Feedback), and OFB (Output Feedback). CBC and ECB modes include padding using PKCS#7.

## Usage

To use the AES implementation in your project, you can directly include the provided source and header files. The source files are located in the `src` directory, and the header files are located in the `include` directory.

```c
#include <aes.h>
.
.
.

int main()
{

    unsigned char key128[] = {"myfirstaescipher"}; // Keys can be 16, 24 and 32 bytes long
    unsigned char iv[] = {"veryfirstinitvec"}; // IV is 16 bytes long in all key sizes and modes of operation!!!

    unsigned char plaintext[] = {"abcdef1123456789  0filip123321a|bcdeabcd  ef1234567890fil??ip123321a{]}  bcde!!!"};
    int plaintext_size = strlen(plaintext);
    int outsize;

    // creating buffer for for outputs - make sure you allocate enough space. The easiest is to just allocate: plaintext_size + AES_BLOCK_SIZE
    unsigned char ciphertext[plaintext_size + AES_BLOCK_SIZE];

    unsigned char decryptedtext[plaintext_size + AES_BLOCK_SIZE];


    // Encrypt decrypt once - use when you just need to encrypt or decrypt something once with one key and one iv
    
    aes_encrypt_once(plaintext, plaintext_size, key128, SIZE_16, CBC, iv, ciphertext, &outsize);

    aes_decrypt_once(ciphertext, outsize, key128, SIZE_16, CBC, iv, decryptedtext, &outsize);

    .
    .
    .

    // Or encrypt and decrypt as API - use when you need to encrypt / decrypt multiple times. Then you should use different iv for every single encrpyt (on every single aes_encrypt)

    // Encrypt

    struct aes_ctx_t aes_encrypt;
    aes_init(&aes_encrypt, key128, SIZE_16, CBC, iv);
    aes_encrypt(&aes_encrypt, plaintext, plaintext_size, ciphertext, &outsize);
    
    // Decrypt
    
    struct aes_ctx_t aes_decrypt;
    
    aes_init(&aes_decrypt, key128, SIZE_16, CBC, iv);
    aes_decrypt(&aes_decrypt, ciphertext, outsize, decryptedtext, &outsize);

    // to change iv
    unsigned char new_iv[] = {"0123456789abcdef"};
    aes_set_iv(&aes_encrypt, new_iv);

    // to change the key
    unsigned char new_key[] = {"0123456789abcdef"};
    aes_set_key(&aes_encrypt, new_key, SIZE_16);  

    // to generate a random iv or key use
    unsigned char iv[16]; 
    generate_random_bytes(iv, 16);

    return 0;
}
```

Additionally, usage examples are provided in the examples directory to demonstrate how to utilize the AES implementation in various scenarios.

Building and Linking
A Makefile is provided to simplify the build process. Running make will compile the source files and create a library file called libaes.a, which should be used for linking.

Here's an example GCC command for linking with the library:

```console
gcc -o aes_test aes_test.c -L<path_to_this_dir>/export/lib -laes -I<path_to_this_dir>/src/include
```
Replace <path_to_this_dir> with the actual path to the project directory.

Note: This implementation is designed for educational purposes only and has not undergone extensive testing. It is not recommended for use in production environments.