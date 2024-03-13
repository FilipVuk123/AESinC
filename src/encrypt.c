#include <encrypt.h>

void sub_bytes(unsigned char *state)
{
    for (int i = 0; i < 16; i++)
        state[i] = get_s_box(state[i]);
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


void cipher(unsigned char *state, unsigned char *expanded_key, int n_rounds)
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