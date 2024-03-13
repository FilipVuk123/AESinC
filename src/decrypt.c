#include <decrypt.h>



void sub_bytes_inv(unsigned char *state)
{
    for (int i = 0; i < 16; i++)
        state[i] = get_rs_box(state[i]);
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


void cipher_inv(unsigned char *state, unsigned char *expanded_key, int n_rounds)
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

void aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum key_size size)
{
    int n_rounds = get_nr(size);

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
