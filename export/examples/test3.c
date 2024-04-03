#include <aes.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

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
    print_buffer_hex(plaintext, plaintext_size);

    printf("\nKEYSIZE 192\n");

    for (int i = 0; i < 5; i++)
    {

        aes_encrypt_once(plaintext, plaintext_size, key192, SIZE_24, i, iv, ciphertext, &outsize);
        printf("\nCiphertext (HEX format):\n");
        print_buffer_hex(ciphertext, outsize);

        aes_decrypt_once(ciphertext, outsize, key192, SIZE_24, i, iv, decryptedtext, &outsize);

        printf("\nDecrypted text (HEX format):\n");
    if (equal_buffers(plaintext, decryptedtext, outsize))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
    }


    printf("\nExiting...\n\n");
    return 0;
}