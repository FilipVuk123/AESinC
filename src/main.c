#include <aes.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    enum key_size size = SIZE_16;

    unsigned char key128[] = {"myfirstaescipher"};
    unsigned char key192[] = {"myfirstaesciphermyfirsta"};
    unsigned char key256[] = {"myfirstaesciphermyfirstaescipher"};
    unsigned char iv[] = {"veryfirstinitvez"};

    unsigned char plaintext[] = {"abcdef1123456789  0filip123321a|bcdeabcd  ef1234567890fil??ip123321a{]}  bcde!!!"};
    int plaintext_size = strlen(plaintext);
    int outsize;

    unsigned char ciphertext[plaintext_size + AES_BLOCK_SIZE];

    unsigned char decryptedtext[plaintext_size + AES_BLOCK_SIZE];

    printf("\nPlaintext (HEX format):\n");
    printBufferHex(plaintext, plaintext_size);

    // printf("\nKEYSIZE 128\n");

    // for (int i = 0; i < 5; i++)
    // {

    //     aes_encrypt(plaintext, plaintext_size, key128, SIZE_16, i, iv, ciphertext, &outsize);
    //     printf("\nCiphertext (HEX format):\n");
    //     printBufferHex(ciphertext, outsize);

    //     aes_decrypt(ciphertext, outsize, key128, SIZE_16, i, iv, decryptedtext, &outsize);

    //     printf("\nDecrypted text (HEX format):\n");
    //     printBufferHex(decryptedtext, outsize);
    // }

    // printf("\nKEYSIZE 192\n");

    // for (int i = 0; i < 5; i++)
    // {
    //     aes_encrypt(plaintext, plaintext_size, key192, SIZE_24, i, iv, ciphertext, &outsize);
    //     printf("\nCiphertext (HEX format):\n");
    //     printBufferHex(ciphertext, outsize);

    //     aes_decrypt(ciphertext, outsize, key192, SIZE_24, i, iv, decryptedtext, &outsize);

    //     printf("\nDecrypted text (HEX format):\n");
    //     printBufferHex(decryptedtext, outsize);
    // }
    
    
    printf("\nKEYSIZE 256\n");
    for (int i = 0; i < 5; i++)
    {
        aes_encrypt(plaintext, plaintext_size, key256, SIZE_32, i, iv, ciphertext, &outsize);
        printf("\nCiphertext (HEX format):\n");
        printBufferHex(ciphertext, outsize);

        aes_decrypt(ciphertext, outsize, key256, SIZE_32, i, iv, decryptedtext, &outsize);

        printf("\nDecrypted text (HEX format):\n");
        printBufferHex(decryptedtext, outsize);
    }
    return 0;
}