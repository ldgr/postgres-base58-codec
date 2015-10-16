#include <gmp.h>
#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/uuid.h"
#include "access/hash.h"
#include "libpq/pqformat.h"
#include "base58_codec.h"


#define UUID_LEN 16


struct pg_uuid_t
{
	unsigned char data[UUID_LEN];
};


#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif


PG_FUNCTION_INFO_V1(base58_encode);

Datum
base58_encode(PG_FUNCTION_ARGS)
{
	pg_uuid_t  *uuid = PG_GETARG_UUID_P(0);

    mpz_t bigint;
    mpz_init(bigint);

    mpz_import(bigint, UUID_LEN, 1, 1, 0, 0, uuid->data);

    char *encoded = encode_base58(bigint);

    size_t len = 160;
    text *new_text = (text *) palloc(len);
    SET_VARSIZE(new_text, len);
    memcpy(VARDATA(new_text), encoded, len);

	PG_RETURN_TEXT_P(new_text);
}


PG_FUNCTION_INFO_V1(base58_decode);


Datum
base58_decode(PG_FUNCTION_ARGS)
{
    text *encoded_text = PG_GETARG_TEXT_P(0);

    char *encoded = VARDATA(encoded_text);
    mpz_t bigint;
    mpz_init(bigint);

    decode_base58(bigint, encoded);

    pg_uuid_t *uuid;
    uuid = (pg_uuid_t *) palloc(sizeof(*uuid));

    char buffer[32];
    mpz_export(uuid->data, NULL, 1, sizeof(char), 0, 0, bigint);

    PG_RETURN_UUID_P(uuid);
}
