#include <aes.h>

void aes_init(struct aes_ctx_t *ctx, unsigned char *key, enum aes_key_size key_size, enum aes_mode mode, unsigned char *iv)
{
    // ctx->key = NULL;
    // ctx->iv = NULL;
    // ctx->expanded_key = NULL;

    ctx->key = malloc(key_size);
    memcpy(ctx->key, key, key_size);

    ctx->iv = malloc(AES_BLOCK_SIZE);
    memcpy(ctx->iv, iv, AES_BLOCK_SIZE);

    ctx->n_rounds = get_nr(key_size);
    ctx->expanded_key_size = AES_BLOCK_SIZE * (ctx->n_rounds + 1);
    ctx->expanded_key = malloc(ctx->expanded_key_size);

    key_expansion(ctx->expanded_key, ctx->key, key_size);

    ctx->mode = mode;
    ctx->size = key_size;
}

void aes_set_iv(struct aes_ctx_t *ctx, unsigned char *iv)
{
    if (ctx->iv != NULL)
        memcpy(ctx->iv, iv, AES_BLOCK_SIZE);
}

void aes_encrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int *out_size)
{
    switch (ctx->mode)
    {
    case CBC:
        aes_cbc_encrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;
    case CFB:
        aes_cfb_encrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;
    case CTR:
        aes_ctr_xxcrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;
    case ECB:
        aes_ecb_encrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, out, out_size);
        break;
    case OFB:
        aes_ofb_xxcrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;

    default:
        break;
    }
}

void aes_decrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int *out_size)
{
    switch (ctx->mode)
    {
    case CBC:
        aes_cbc_decrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;
    case CFB:
        aes_cfb_decrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;
    case CTR:
        aes_ctr_xxcrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;
    case ECB:
        aes_ecb_decrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, out, out_size);
        break;
    case OFB:
        aes_ofb_xxcrypt(in, in_size, ctx->expanded_key, ctx->n_rounds, ctx->iv, out, out_size);
        break;

    default:
        break;
    }
}

void aes_destroy(struct aes_ctx_t *ctx)
{
    if (ctx->key != NULL){
        free(ctx->key);
        ctx->key = NULL;
    }
    if (ctx->iv != NULL){
        free(ctx->iv);
        ctx->iv = NULL;
    }
    if (ctx->expanded_key != NULL){
        free(ctx->expanded_key);
        ctx->expanded_key = NULL;
    }
}

void aes_encrypt_once(unsigned char *in, int in_size, unsigned char *key, enum aes_key_size key_size, enum aes_mode mode, unsigned char *iv, unsigned char *out, int *out_size)
{
    struct aes_ctx_t aes;
    aes_init(&aes, key, key_size, mode, iv);
    aes_encrypt(&aes, in, in_size, out, out_size);
    aes_destroy(&aes);
}

void aes_decrypt_once(unsigned char *in, int in_size, unsigned char *key, enum aes_key_size key_size, enum aes_mode mode, unsigned char *iv, unsigned char *out, int *out_size)
{
    struct aes_ctx_t aes;
    aes_init(&aes, key, key_size, mode, iv);
    aes_decrypt(&aes, in, in_size, out, out_size);
    aes_destroy(&aes);
}
