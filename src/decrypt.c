#include <decrypt.h>



void sub_bytes_inv(unsigned char *state)
{
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
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
    column[0] = gf_mult(tmp[0], 14) ^
                gf_mult(tmp[3], 9) ^
                gf_mult(tmp[2], 13) ^
                gf_mult(tmp[1], 11);
    column[1] = gf_mult(tmp[1], 14) ^
                gf_mult(tmp[0], 9) ^
                gf_mult(tmp[3], 13) ^
                gf_mult(tmp[2], 11);
    column[2] = gf_mult(tmp[2], 14) ^
                gf_mult(tmp[1], 9) ^
                gf_mult(tmp[0], 13) ^
                gf_mult(tmp[3], 11);
    column[3] = gf_mult(tmp[3], 14) ^
                gf_mult(tmp[2], 9) ^
                gf_mult(tmp[1], 13) ^
                gf_mult(tmp[0], 11);
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

    unsigned char round_key[AES_BLOCK_SIZE];
    create_round_key(expanded_key + AES_BLOCK_SIZE * n_rounds, round_key);
    add_round_key(state, round_key);

    for (int i = n_rounds - 1; i > 0; i--)
    {
        create_round_key(expanded_key + AES_BLOCK_SIZE * i, round_key);
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

void aes_decrypt_block(unsigned char *input, unsigned char *output, int num_rounds, unsigned char* expanded_key)
{
    unsigned char block[AES_BLOCK_SIZE];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            block[(i + (j * 4))] = input[(i * 4) + j];
    }


    cipher_inv(block, expanded_key, num_rounds);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[(i * 4) + j] = block[(i + (j * 4))];
        }
    }
}
