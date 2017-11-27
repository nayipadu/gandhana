#ifndef HASH_INTERNAL_H
#define HASH_INTERNAL_H

#include <list.h>
#include <stdlib.h>

#define HASH_MALLOC malloc
#define HASH_FREE free

#define HASH_GET_INDEX(tbl, key)		(tbl->hash_fn(key, tbl->num_buckets))
#define GET_HASH_IDX_LIST_HEAD(tbl, idx)	(tbl->buckets + (idx))

typedef bucket_t (*hash_fn_t) (voidp key, bucket_t comparewith);
typedef int (*compare_fn_t) (voidp key, voidp comparewith);
typedef void (*dump_fn_t) (voidp key, voidp data);

typedef struct hash_table {
    bucket_t num_buckets;
    compare_fn_t comapare_fn;
    hash_fn_t hash_fn;
    dump_fn_t dump_fn;
    list_head_t *buckets;
}hash_table_t;

#endif /* HASH_INTERNAL_H */
