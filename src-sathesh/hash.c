
#include <hash.h>
#include <string.h>
#include "hash_internal.h"

hashCookie hash_init(bucket_t num_buckets,
                     hash_fn_t hash_fn,  
                     compare_fn_t comapare_fn,
                     dump_fn_t dump_fn)
{
    hash_table_t *hash_table = HASH_MALLOC(sizeof(hash_table_t));
    if (!hash_table)
        return NULL;

    hash_table->buckets = HASH_MALLOC(num_buckets * sizeof (list_head_t));
    if (!hash_table->buckets) {
        HASH_FREE(hash_table);
        return NULL;
    }

    memset(hash_table->buckets, 0, num_buckets * sizeof (list_head_t));
    hash_table->hash_fn = hash_fn;
    hash_table->comapare_fn = comapare_fn;
    hash_table->dump_fn = dump_fn;
    return (hashCookie) hash_table;
}

int hash_insert(hashCookie cookie, voidp key, voidp data)
{
    hash_table_t *htable = (hash_table_t*) cookie;
    unsigned int hash_idx;
    list_head_t *lh;

    if (!htable)
        return -1;

    hash_idx = HASH_GET_INDEX(htable, key);
    lh = GET_HASH_IDX_LIST_HEAD(htable, hash_idx);
    return SLIST_INSERT_AT_HEAD(lh, data);
}

voidp hash_lookup(hashCookie cookie, voidp key)
{
    hash_table_t *htable = (hash_table_t*) cookie;
    unsigned int hash_idx;
    list_head_t *lh;

    if (!htable)
        return NULL;

    hash_idx = HASH_GET_INDEX(htable, key);
    lh = GET_HASH_IDX_LIST_HEAD(htable, hash_idx);
    return SLIST_LOOKUP(lh, htable->comapare_fn, key);
}
