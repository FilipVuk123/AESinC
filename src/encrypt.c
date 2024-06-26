#include <encrypt.h>

void sub_bytes(unsigned char *state)
{
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
        state[i] = get_s_box(state[i]);
}



// static void shift_row(unsigned char *state, int nbr)
// {
//     for (int i = 0; i < nbr; i++)
//     {
//         rotate_word(state);
//     }
// }

// void shift_rows(unsigned char *state)
// {
//     for (int i = 0; i < 4; i++)
//     {
//         shift_row(state + i * 4, i);
//     }
// }

void shift_rows(unsigned char *state){
    unsigned char tmp;

    // Shift first row once to the left
    tmp = state[4];
    state[4] = state[5];
    state[5] = state[6];
    state[6] = state[7];
    state[7] = tmp;

    // Shift second row twice to the left
    tmp = state[8];
    state[8] = state[10];
    state[10] = tmp;
    tmp = state[9];
    state[9] = state[11];
    state[11] = tmp;

    // Shift third row three times to the left
    tmp = state[12];
    state[12] = state[15];
    state[15] = state[14];
    state[14] = state[13];
    state[13] = tmp;
}

static void mix_column(unsigned char *column)
{
    unsigned char tmp[4];
    for (int i = 0; i < 4; i++)
    {
        tmp[i] = column[i];
    }
    column[0] = gf_mult(tmp[0], 2) ^
                gf_mult(tmp[3], 1) ^
                gf_mult(tmp[2], 1) ^
                gf_mult(tmp[1], 3);

    column[1] = gf_mult(tmp[1], 2) ^
                gf_mult(tmp[0], 1) ^
                gf_mult(tmp[3], 1) ^
                gf_mult(tmp[2], 3);

    column[2] = gf_mult(tmp[2], 2) ^
                gf_mult(tmp[1], 1) ^
                gf_mult(tmp[0], 1) ^
                gf_mult(tmp[3], 3);

    column[3] = gf_mult(tmp[3], 2) ^
                gf_mult(tmp[2], 1) ^
                gf_mult(tmp[1], 1) ^
                gf_mult(tmp[0], 3);
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
    unsigned char round_key[AES_BLOCK_SIZE];
    create_round_key(expanded_key, round_key);
    add_round_key(state, round_key);

    for (int i = 1; i < n_rounds; i++)
    {
        create_round_key(expanded_key + AES_BLOCK_SIZE * i, round_key);

        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, round_key);
    }
    create_round_key(expanded_key + AES_BLOCK_SIZE * n_rounds, round_key);
    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, round_key);
}


void aes_encrypt_block(unsigned char *input, unsigned char *output, int num_rounds, unsigned char* expanded_key)
{

    unsigned char block[AES_BLOCK_SIZE];


    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++){   
            block[(i + (j * 4))] = input[(i * 4) + j];
        }
    }


    cipher(block, expanded_key, num_rounds);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[(i * 4) + j] = block[(i + (j * 4))];
        }
    }
}
