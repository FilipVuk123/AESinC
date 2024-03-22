#include <aes.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    enum key_size size = SIZE_16;

    unsigned char key3[] = {"myfirstaescipher"};
    unsigned char nonce[] = {"veryfirstinitvez"};

    unsigned char plaintext3[] = {"abcdef1234567890filip123321abcdeabcdef1234567890filip123321abcde!!!"};

    int outsize;

    unsigned char ciphertext3[100];

    unsigned char decryptedtext3[100];

    printf("\nPlaintext (HEX format):\n");
    printBufferHex(plaintext3, 67);

    aes_cbc_encrypt(plaintext3, 67, key3, SIZE_16, nonce, ciphertext3, &outsize);

    printf("\nCiphertext (HEX format):\n");
    printBufferHex(ciphertext3, outsize);


    aes_cbc_decrypt(ciphertext3, outsize, key3, SIZE_16, nonce, decryptedtext3, &outsize);

    printf("\nDecrypted text (HEX format):\n");
    printBufferHex(decryptedtext3, outsize);

    return 0;

}