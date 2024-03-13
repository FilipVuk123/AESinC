#include <aes.h>

unsigned char sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

unsigned char rsbox[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

static const uint8_t rconst[11] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

static unsigned char getRConstValue(unsigned char ch)
{
    return rconst[ch];
}

static unsigned char getSBoxValue(unsigned char ch)
{
    return sbox[ch];
}

static unsigned char getRSBoxValue(unsigned char ch)
{
    return rsbox[ch];
}

static void rotate_word(unsigned char *word)
{
    unsigned char word_0 = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = word_0;
}

static void rotate_word_inv(unsigned char *word)
{
    unsigned char word_3 = word[3];
    word[3] = word[2];
    word[2] = word[1];
    word[1] = word[0];
    word[0] = word_3;
}

static void key_schedule(unsigned char *word, int iter)
{
    rotate_word(word);
    for (int i = 0; i < 4; i++)
    {
        word[i] = getSBoxValue(word[i]);
    }
    word[0] = word[0] ^ getRConstValue(iter);
}

void key_expansion(unsigned char *expanded_key, unsigned char *key, enum keySize size)
{
    printf("Key expansion!");
    int n_k;
    int n_rounds;
    switch (size)
    {
    case SIZE_16:
        n_k = 4;
        n_rounds = 10;
        break;
    case SIZE_24:
        n_k = 6;
        n_rounds = 12;
        break;
    case SIZE_32:
        n_k = 8;
        n_rounds = 14;
        break;
    default:
        n_k = 4;
        n_rounds = 10;
        break;
    }

    for (int i = 0; i <= n_k; i++)
    {
        expanded_key[4 * i + 0] = key[4 * i + 0];
        expanded_key[4 * i + 1] = key[4 * i + 1];
        expanded_key[4 * i + 2] = key[4 * i + 2];
        expanded_key[4 * i + 3] = key[4 * i + 3];
    }

    unsigned char tmp[4] = {0};
    for (int i = n_k; i < 4 * (n_rounds + 1); i++)
    {
        for (int k = 0; k < 4; k++)
        {
            tmp[k] = expanded_key[(i - 1) * 4 + k];
        }

        if (i % n_k == 0)
        {
            key_schedule(tmp, i / n_k);
        }
        else if (n_k > 6 && i % n_k == 4)
        {
            for (int k = 0; k < 4; k++)
            {
                tmp[k] = getSBoxValue(tmp[k]);
            }
        }
        for (int k = 0; k < 4; k++)
        {
            expanded_key[4 * i + k] = expanded_key[(i - n_k) * 4 + k] ^ tmp[k];
        }
    }
}

void key_expansion_2(unsigned char *expanded_key, unsigned char *key, enum keySize size, size_t expanded_key_size)
{
    printf("Key expansion 2!");
    int currentSize = 0;

    for (int i = 0; i < size; i++)
    {
        expanded_key[i] = key[i];
    }
    currentSize += size;

    int rconIteration = 1;
    unsigned char t[4] = {0};

    while (currentSize < expanded_key_size)
    {
        for (int i = 0; i < 4; i++)
        {
            t[i] = expanded_key[(currentSize - 4) + i];
        }

        if (currentSize % size == 0)
        {
            key_schedule(t, rconIteration);
            rconIteration++;
        }

        if (size == SIZE_32 && ((currentSize % size) == 16))
        {
            for (int i = 0; i < 4; i++)
            {
                t[i] = getSBoxValue(t[i]);
            }
        }

        for (int i = 0; i < 4; i++)
        {
            expanded_key[currentSize] = expanded_key[currentSize - size] ^ t[i];
            currentSize++;
        }
    }
}

void sub_bytes(unsigned char *state)
{
    for (int i = 0; i < 16; i++)
        state[i] = getSBoxValue(state[i]);
}

void sub_bytes_inv(unsigned char *state)
{
    for (int i = 0; i < 16; i++)
        state[i] = getRSBoxValue(state[i]);
}

static void shift_row(unsigned char *state, int nbr)
{
    for (int i = 0; i < nbr; i++)
    {
        rotate_word(state);
    }
}

void shift_rows(unsigned char *state)
{
    for (int i = 0; i < 4; i++)
    {
        shift_row(state + i * 4, i);
    }
}

static void shift_row_inv(unsigned char *state, int nbr)
{
    unsigned char tmp;

    for (int i = 0; i < nbr; i++)
    {
        rotate_word_inv(state);
    }
}

void shift_rows_inv(unsigned char *state)
{
    for (int i = 0; i < 4; i++)
    {
        shift_row_inv(state + i * 4, i);
    }
}

void add_round_key(unsigned char *state, unsigned char *round_key)
{
    for (int i = 0; i < 16; i++)
    {
        state[i] = state[i] ^ round_key[i];
    }
}

static unsigned char galois_multiplication(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    unsigned char hi_bit_set;
    for (int counter = 0; counter < 8; counter++)
    {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

static void mix_column(unsigned char *column)
{
    unsigned char tmp[4];
    for (int i = 0; i < 4; i++)
    {
        tmp[i] = column[i];
    }
    column[0] = galois_multiplication(tmp[0], 2) ^
                galois_multiplication(tmp[3], 1) ^
                galois_multiplication(tmp[2], 1) ^
                galois_multiplication(tmp[1], 3);

    column[1] = galois_multiplication(tmp[1], 2) ^
                galois_multiplication(tmp[0], 1) ^
                galois_multiplication(tmp[3], 1) ^
                galois_multiplication(tmp[2], 3);

    column[2] = galois_multiplication(tmp[2], 2) ^
                galois_multiplication(tmp[1], 1) ^
                galois_multiplication(tmp[0], 1) ^
                galois_multiplication(tmp[3], 3);

    column[3] = galois_multiplication(tmp[3], 2) ^
                galois_multiplication(tmp[2], 1) ^
                galois_multiplication(tmp[1], 1) ^
                galois_multiplication(tmp[0], 3);
}

void mix_columns(unsigned char *state)
{
    unsigned char column[4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            column[j] = state[(j * 4) + i];
        }

        mix_column(column);

        for (int j = 0; j < 4; j++)
        {
            state[(j * 4) + i] = column[j];
        }
    }
}

static void mix_column_inv(unsigned char *column)
{
    unsigned char tmp[4];
    int i;
    for (i = 0; i < 4; i++)
    {
        tmp[i] = column[i];
    }
    column[0] = galois_multiplication(tmp[0], 14) ^
                galois_multiplication(tmp[3], 9) ^
                galois_multiplication(tmp[2], 13) ^
                galois_multiplication(tmp[1], 11);
    column[1] = galois_multiplication(tmp[1], 14) ^
                galois_multiplication(tmp[0], 9) ^
                galois_multiplication(tmp[3], 13) ^
                galois_multiplication(tmp[2], 11);
    column[2] = galois_multiplication(tmp[2], 14) ^
                galois_multiplication(tmp[1], 9) ^
                galois_multiplication(tmp[0], 13) ^
                galois_multiplication(tmp[3], 11);
    column[3] = galois_multiplication(tmp[3], 14) ^
                galois_multiplication(tmp[2], 9) ^
                galois_multiplication(tmp[1], 13) ^
                galois_multiplication(tmp[0], 11);
}

void mix_columns_inv(unsigned char *state)
{
    unsigned char column[4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            column[j] = state[(j * 4) + i];
        }

        mix_column_inv(column);

        for (int j = 0; j < 4; j++)
        {
            state[(j * 4) + i] = column[j];
        }
    }
}

void create_round_key(unsigned char *expanded_key, unsigned char *round_key)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            round_key[(i + (j * 4))] = expanded_key[(i * 4) + j];
        }
    }
}

static void cipher(unsigned char *state, unsigned char *expanded_key, int n_rounds)
{
    unsigned char round_key[16];
    create_round_key(expanded_key, round_key);
    add_round_key(state, round_key);

    for (int i = 1; i < n_rounds; i++)
    {
        create_round_key(expanded_key + 16 * i, round_key);

        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, round_key);
    }
    create_round_key(expanded_key + 16 * n_rounds, round_key);
    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, round_key);
}

static void cipher_inv(unsigned char *state, unsigned char *expanded_key, int n_rounds)
{

    unsigned char round_key[16];
    create_round_key(expanded_key + 16 * n_rounds, round_key);
    add_round_key(state, round_key);

    for (int i = n_rounds - 1; i > 0; i--)
    {
        create_round_key(expanded_key + 16 * i, round_key);
        shift_rows_inv(state);
        sub_bytes_inv(state);
        add_round_key(state, round_key);
        mix_columns_inv(state);
    }
    create_round_key(expanded_key, round_key);
    shift_rows_inv(state);
    sub_bytes_inv(state);
    add_round_key(state, round_key);
}

void aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size)
{
    int n_rounds;
    switch (size)
    {
    case SIZE_16:
        n_rounds = 10;
        break;
    case SIZE_24:
        n_rounds = 12;
        break;
    case SIZE_32:
        n_rounds = 14;
        break;
    default:
        n_rounds = 10;
        break;
    }

    unsigned char block[16];

    int expanded_key_size = (16 * (n_rounds + 1));
    unsigned char expanded_key[expanded_key_size];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            block[(i + (j * 4))] = input[(i * 4) + j];
    }

    // key_expansion_2(expanded_key, key, size, expanded_key_size);
    key_expansion(expanded_key, key, size);

    cipher(block, expanded_key, n_rounds);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[(i * 4) + j] = block[(i + (j * 4))];
        }
    }
}

void aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size)
{
    int n_rounds;
    switch (size)
    {
    case SIZE_16:
        n_rounds = 10;
        break;
    case SIZE_24:
        n_rounds = 12;
        break;
    case SIZE_32:
        n_rounds = 14;
        break;
    default:
        n_rounds = 10;
        break;
    }

    unsigned char block[16];

    int expanded_key_size = (16 * (n_rounds + 1));
    unsigned char expanded_key[expanded_key_size];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            block[(i + (j * 4))] = input[(i * 4) + j];
    }

    // key_expansion_2(expanded_key, key, size, expanded_key_size);
    
    key_expansion(expanded_key, key, size);

    cipher_inv(block, expanded_key, n_rounds);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[(i * 4) + j] = block[(i + (j * 4))];
        }
    }
}