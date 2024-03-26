#include <aes.h>

enum aes_status aes_init(struct aes_ctx_t *ctx, unsigned char *key, enum aes_key_size key_size, enum aes_mode mode, unsigned char *iv)
{
    memset(ctx->expanded_key, 0, 240);
    memset(ctx->key, 0, SIZE_32);
    memset(ctx->iv, 0, AES_BLOCK_SIZE);

    if (NULL == ctx || NULL == key || NULL == iv)
    {
        return ERROR_INVALID_PARAMETAR;
    }

    switch (mode)
    {
    case CBC:
    case CFB:
    case CTR:
    case ECB:
    case OFB:
        break;
    default:
        return ERROR_UNKNOWN_MODE;
    }

    switch (key_size)
    {
    case SIZE_16:
    case SIZE_24:
    case SIZE_32:
        break;
    default:
        return ERROR_UNKNOWN_KEY_SIZE;
    }

    ctx->mode = mode;
    ctx->size = key_size;

    ctx->n_rounds = -1;

    memcpy(ctx->iv, iv, AES_BLOCK_SIZE);

    memcpy(ctx->key, key, key_size);

    ctx->n_rounds = get_nr(key_size);
    ctx->expanded_key_size = AES_BLOCK_SIZE * (ctx->n_rounds + 1);

    key_expansion(ctx->expanded_key, ctx->key, key_size);

    return SUCCESS;
}

enum aes_status aes_set_iv(struct aes_ctx_t *ctx, unsigned char *iv)
{
    if (NULL == iv || NULL == ctx)
    {
        return ERROR_INVALID_PARAMETAR;
    }
    memcpy(ctx->iv, iv, AES_BLOCK_SIZE);
    return SUCCESS;
}

enum aes_status aes_set_key(struct aes_ctx_t *ctx, unsigned char *key, enum aes_key_size key_size)
{
    if (NULL == key || NULL == ctx)
    {
        return ERROR_INVALID_PARAMETAR;
    }

    switch (key_size)
    {
    case SIZE_16:
    case SIZE_24:
    case SIZE_32:
        break;
    default:
        return ERROR_UNKNOWN_KEY_SIZE;
    }
    memcpy(ctx->key, key, key_size);
    ctx->size = key_size;

    ctx->n_rounds = get_nr(key_size);
    ctx->expanded_key_size = AES_BLOCK_SIZE * (ctx->n_rounds + 1);

    key_expansion(ctx->expanded_key, ctx->key, key_size);
    return SUCCESS;
}

enum aes_status aes_encrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int *out_size)
{

    if (NULL == in || NULL == ctx || NULL == out || NULL == out_size)
    {
        return ERROR_INVALID_PARAMETAR;
    }
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
    return SUCCESS;
}

enum aes_status aes_decrypt(struct aes_ctx_t *ctx, unsigned char *in, int in_size, unsigned char *out, int *out_size)
{
    if (NULL == in || NULL == ctx || NULL == out || NULL == out_size)
    {
        return ERROR_INVALID_PARAMETAR;
    }

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
    return SUCCESS;
}

enum aes_status aes_encrypt_once(unsigned char *in, int in_size, unsigned char *key, enum aes_key_size key_size, enum aes_mode mode, unsigned char *iv, unsigned char *out, int *out_size)
{
    struct aes_ctx_t aes;
    enum aes_status res = aes_init(&aes, key, key_size, mode, iv);
    if (res != SUCCESS){
        return res;
    }
    res = aes_encrypt(&aes, in, in_size, out, out_size);
    if (res != SUCCESS){
        return res;
    }
    return SUCCESS;
}

enum aes_status aes_decrypt_once(unsigned char *in, int in_size, unsigned char *key, enum aes_key_size key_size, enum aes_mode mode, unsigned char *iv, unsigned char *out, int *out_size)
{
    struct aes_ctx_t aes;
    enum aes_status res = aes_init(&aes, key, key_size, mode, iv);
    if (res != SUCCESS){
        return res;
    }
    res = aes_decrypt(&aes, in, in_size, out, out_size);
    if (res != SUCCESS){
        return res;
    }
    return SUCCESS;
}
