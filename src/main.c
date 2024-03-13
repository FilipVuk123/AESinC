#include <aes.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    enum key_size size = SIZE_16;

    int expandedKeySize = 176;

    unsigned char expandedKey[expandedKeySize];

    unsigned char key[16] = {'m', 'y', 'f', 'i', 'r', 's', 't', 'a', 'e', 's', 'c', 'i', 'p', 'h', 'e', 'r'};


    unsigned char plaintext[16] = {'a', 'b', 'c', 'd', 'e', 'f', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    unsigned char ciphertext[16];

    unsigned char decryptedtext[16];

    int i;


    printf("\nCipher Key (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", key[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    key_expansion_2(expandedKey, key, size, expandedKeySize);

    printf("\nExpanded Key (HEX format):\n");

    for (i = 0; i < expandedKeySize; i++)
    {
        printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    printf("\nPlaintext (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", plaintext[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    aes_encrypt(plaintext, ciphertext, key, size);

    printf("\nCiphertext (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", ciphertext[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    aes_decrypt(ciphertext, decryptedtext, key, size);

    printf("\nDecrypted text (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", decryptedtext[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    return 0;

}