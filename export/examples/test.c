#include <aes.h>
#include <stdio.h>

int main()
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

    printf("\nKEYSIZE 128\n");
    timer clock_encrypt, clock_decrypt;
    
    for (int i = 0; i < 5; i++)
    {
        clock_encrypt = time_now();
        aes_encrypt_once(plaintext, plaintext_size, key128, SIZE_16, i, iv, ciphertext, &outsize);
        printf("Encrypt time in ms: %f\n", get_time_diff_msec(clock_encrypt, time_now()));
        printf("\nCiphertext (HEX format):\n");
        print_buffer_hex(ciphertext, outsize);
        clock_decrypt = time_now();
        aes_decrypt_once(ciphertext, outsize, key128, SIZE_16, i, iv, decryptedtext, &outsize);
        printf("Decrypt time in ms: %f\n", get_time_diff_msec(clock_decrypt, time_now()));
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