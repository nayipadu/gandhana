
#include "hash.h"
#include <stdlib.h>

typedef struct _hash {
   bucket_t (*hash_function)(voidp, bucket_t);
   bucket_t (*compare_function)(voidp, voidp);
   void (*dump_function)(voidp, voidp);
   bucket_t num_buckets;
   void **hashtable;

} hash_t;

// #### LL Functions


typedef struct _ll {
   struct _ll *next;
   void *key;
   void *value;
} llnode;

static llnode *
ll_newnode(void *key, void *value)
{
   llnode *node;
   node = malloc(sizeof(llnode));
   if (!node)
      return NULL;

   node->next = NULL;
   node->key = key;
   node->value = value;

   return node;
}

static void
ll_insert( llnode **head, llnode *node)
{
   // Insert at head to avoid traversing
   // If head is NULL, node becomes head
   node->next = *head;
   *head = node;
   return;
}

#define SLL_INIT(phead) phead=NULL
#define SLL_NEXT(node) node->next

// read as singly linked list, for each node
#define SLL_FOREACH(head, node) \
   for ((node) = head; (node); (node) = SLL_NEXT(node))

// #### LL fucntions end here

static int
hash_find_lookup_in_bucket(hash_t *handler, bucket_t index, voidp key)
{
   llnode *node;

   SLL_FOREACH(handler->hashtable[index], node) {
      if(!handler->compare_function(node->key, key))
         continue;
      return 1; // key exists
   }
   return 0; // key does not exist
}

void
hashtable_dump(hashCookie cookie)
{
   hash_t *handler = (hash_t *) cookie;
   llnode *node;
   int i;

   // go over each bucket and each node in every bucket. print key and value
   for (i = 0; i < handler->num_buckets; i++) {
      SLL_FOREACH(handler->hashtable[i], node) {
         handler->dump_function(node->key, node->value);
      }
   }
}

int
hash_insert(hashCookie cookie, voidp key, voidp value)
{
   hash_t *handler = (hash_t *) cookie;
   bucket_t buc_num;
   llnode *node;

   buc_num = handler->hash_function( key, handler->num_buckets );
   if (buc_num == -1) {
      // something wrong in hash function.
      return -1;
   }

   if(hash_find_lookup_in_bucket(handler, buc_num, key)) {
      // key already in hashtable
      // TODO: this is the default behavior right? duplicates are detected ?
      return 1;
   }

   /* Insert node in this bucket */
   node = ll_newnode(key, value);
   if (!node) {
      // malloc failure
      return -1;
   }
   ll_insert((llnode **)&handler->hashtable[ buc_num ], node);
   return 0;
}

hashCookie
hash_init(bucket_t num_buckets,
          bucket_t (*hash_function)(voidp, bucket_t),
          bucket_t (*compare_function)(voidp, voidp),
          void (*dump_function)(voidp, voidp))
{
   hash_t *handler;
   void **hashtable;
   int i;

   if (!hash_function || !compare_function || num_buckets < 1) {
      return NULL;
   }

   handler = (hash_t *) malloc (sizeof(hash_t));
   if (!handler) {
      return NULL;
   }

   handler->num_buckets = num_buckets;
   handler->hash_function = hash_function;
   handler->compare_function = compare_function;
   handler->dump_function = dump_function;

   // need an array of pointers for hashtable. Pointers holding
   // head of linked list
   hashtable = (void **)malloc(num_buckets * (sizeof(u_int32_t *)));
   if (!hashtable) {
      return NULL;
   }
   /* Inititalize linked list head in all buckets */
   for (i=0; i < num_buckets; i++) {
      SLL_INIT(hashtable[i]);
   }
   handler->hashtable = (void **)hashtable;

   return (hashCookie) handler;
}


