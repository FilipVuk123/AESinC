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

    printf("\nCipher Key (HEX format):\n");
    printBufferHex(key, 16);
    

    key_expansion_2(expandedKey, key, size, expandedKeySize);

    printf("\nExpanded Key (HEX format):\n");

    for (int i = 0; i < expandedKeySize; i++)
    {
        printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    printf("\nPlaintext (HEX format):\n");
    printBufferHex(plaintext, 16);

    aes_encrypt(plaintext, ciphertext, key, size);

    printf("\nCiphertext (HEX format):\n");
    printBufferHex(ciphertext, 16);

    aes_decrypt(ciphertext, decryptedtext, key, size);

    printf("\nDecrypted text (HEX format):\n");
    printBufferHex(decryptedtext, 16);

    return 0;

}