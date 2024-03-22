#include <aes.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    enum key_size size = SIZE_16;

    int expandedKeySize = 176;

    unsigned char expandedKey[expandedKeySize];

    unsigned char key[] = {"myfirstaescipher"};

    unsigned char plaintext[] = {"filip123321abcde"};

    unsigned char ciphertext[16];

    unsigned char decryptedtext[16];

    printf("\nCipher Key (HEX format):\n");
    printBufferHex(key, 16);
    

    key_expansion(expandedKey, key, size);

    printf("\nExpanded Key (HEX format):\n");

    for (int i = 0; i < expandedKeySize; i++)
    {
        printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    printf("\nPlaintext (HEX format):\n");
    printBufferHex(plaintext, 16);

    aes_encrypt_block(plaintext, ciphertext, key, size);

    printf("\nCiphertext (HEX format):\n");
    printBufferHex(ciphertext, 16);

    aes_decrypt_block(ciphertext, decryptedtext, key, size);

    printf("\nDecrypted text (HEX format):\n");
    printBufferHex(decryptedtext, 16);


    // unsigned char key1[] = {"myfirstaescipher"};

    // unsigned char plaintext1[] = {"abcdef1234567890filip123321abcde"};

    // unsigned char ciphertext1[32];

    // unsigned char decryptedtext1[32];

    // printf("\nPlaintext (HEX format):\n");
    // printBufferHex(plaintext1, 32);

    // aes_ecb_encrypt(plaintext1, 32, key1, SIZE_16, ciphertext1, NULL);

    // printf("\nCiphertext (HEX format):\n");
    // printBufferHex(ciphertext1, 32);

    // aes_ecb_decrypt(ciphertext1, 32, key1, SIZE_16, decryptedtext1, NULL);

    // printf("\nDecrypted text (HEX format):\n");
    // printBufferHex(decryptedtext1, 32);


    // unsigned char key2[] = {"myfirstaescipher"};
    // unsigned char iv[] = {"veryfirstinitvec"};

    // unsigned char plaintext2[] = {"abcdef1234567890filip123321abcdeabcdef1234567890filip123321abcde"};

    // unsigned char ciphertext2[64];

    // unsigned char decryptedtext2[64];

    // printf("\nPlaintext (HEX format):\n");
    // printBufferHex(plaintext2, 64);

    // aes_cbc_encrypt(plaintext2, 64, key2, SIZE_16, iv, ciphertext2, NULL);

    // printf("\nCiphertext (HEX format):\n");
    // printBufferHex(ciphertext2, 64);

    // aes_cbc_decrypt(ciphertext2, 64, key2, SIZE_16, iv, decryptedtext2, NULL);

    // printf("\nDecrypted text (HEX format):\n");
    // printBufferHex(decryptedtext2, 64);


    unsigned char key3[] = {"myfirstaescipher"};
    unsigned char nonce[] = {"veryfirstinitvez"};

    unsigned char plaintext3[] = {"abcdef1234567890filip123321abcdeabcdef1234567890filip123321abcde!!!"};

    int outsize;

    unsigned char ciphertext3[67];

    unsigned char decryptedtext3[67];

    printf("\nPlaintext (HEX format):\n");
    printBufferHex(plaintext3, 67);

    aes_ofb_xxcrypt(plaintext3, 67, key3, SIZE_16, nonce, ciphertext3, &outsize);

    printf("\nCiphertext (HEX format):\n");
    printBufferHex(ciphertext3, 67);


    aes_ofb_xxcrypt(ciphertext3, 67, key3, SIZE_16, nonce, decryptedtext3, &outsize);

    printf("\nDecrypted text (HEX format):\n");
    printBufferHex(decryptedtext3, 67);

    return 0;

}