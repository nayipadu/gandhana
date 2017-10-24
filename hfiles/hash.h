
#ifndef __INCLUDE_HASH__
#define __INCLUDE_HASH__

#include "common.h"

typedef u_int32_t bucket_t;
typedef voidp hashCookie;

// Collision resolution is linked list.
hashCookie hash_init(bucket_t num_buckets,
                bucket_t (*hash_function)(voidp, bucket_t),
                bucket_t (*compare_function)(voidp, voidp),
                void (*dump_function)(voidp, voidp, bucket_t index));

/*
 *  0 : success
 * -1 : failure
 *  1 : Key already exists
 */
int
hash_insert(hashCookie handler, voidp key, voidp data);

void
hash_remove(hashCookie handler, voidp key);

voidp
hash_lookup(hashCookie handler, voidp key);

bool
hashtable_dump(hashCookie handler);

#endif

