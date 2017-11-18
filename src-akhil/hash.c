
#include "../include/hash.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _hash {
   bucket_t (*hash_function)(voidp, bucket_t);
   int (*compare_function)(voidp, voidp comparewith);
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

static voidp
hash_find_lookup_in_bucket(hash_t *handler, bucket_t index, voidp key)
{
   llnode *node;

   // walk through the linked list and find the key
   SLL_FOREACH(handler->hashtable[index], node) {
      if(!handler->compare_function(node->key, key))
         continue;
      return node->value; // key exists
   }
   return 0; // key does not exist
}

void
hashtable_dump(hashCookie cookie)
{
   hash_t *handler = (hash_t *) cookie;
   llnode *node;
   unsint32_t i;

   // go over each bucket and each node in every bucket. print key and value
   for (i = 0; i < handler->num_buckets; i++) {
      trace("bucket -> %lu\n", i);
      SLL_FOREACH(handler->hashtable[i], node) {
         handler->dump_function(node->key, node->value);
      }
   }
   trace("\n");
}

voidp
hash_lookup(hashCookie cookie, voidp key)
{
   hash_t *handler = (hash_t *) cookie;
   bucket_t buc_num;
   voidp value;
    
   buc_num = handler->hash_function( key, handler->num_buckets );
   trace("bucket number is: %lu\n", buc_num);

   value = hash_find_lookup_in_bucket(handler, buc_num, key);
   return value;
}

int
hash_insert(hashCookie cookie, voidp key, voidp value)
{
   hash_t *handler = (hash_t *) cookie;
   bucket_t buc_num;
   llnode *node;

   trace("Entering. value is %s\n", (char *)value);
   if (!hash_lookup(cookie, key)) {
      // TODO: this is the default behavior right? duplicates are detected ?
      return 1; // duplicate entry
   }

   //TODO: Need optimization. buc_num obtained while lookup, use it
   buc_num = handler->hash_function( key, handler->num_buckets );
   trace("create a new node to insert");
   /* Insert node in this bucket */
   node = ll_newnode(key, value);
   if (!node) {
      // malloc failure
      return -1;
   }
   ll_insert((llnode **)&handler->hashtable[ buc_num ], node);
   return 0;
}

//assuming key as long unsigned int and value as string in all the default functions
// returns true or false
static int
def_comparefunction(voidp key, voidp comparewith)
{
   return key == comparewith;
}

static bucket_t
def_hashfunction(voidp key, bucket_t num_buckets)
{
   return ((unsint32_t)key) % num_buckets; 
}

static void
def_dumpfunction(voidp key, voidp value)
{
   trace("   Key -> %lu\n", (unsint32_t)key);
   trace("   value -> %s\n", (char *) value);
}

hashCookie
hash_init(bucket_t num_buckets,
          bucket_t (*hash_function)(voidp key, bucket_t num_buckets),
          int (*compare_function)(voidp key, voidp comparewith),
          void (*dump_function)(voidp, voidp))
{
   hash_t *handler;
   void **hashtable;
   int i;

   if (num_buckets == 0) {
      trace("check input parameters\n");
      return NULL;
   }

   handler = (hash_t *) malloc (sizeof(hash_t));
   if (!handler) {
      return NULL;
   }

   handler->num_buckets = num_buckets;
   if (!hash_function) {
      // Set default hash function treating the key as a 32 bit integer
      handler->hash_function = def_hashfunction;
   } else {
      handler->hash_function = hash_function;
   }
		  
   if (!compare_function) {
      // Set default compare function treating key as a 32 bit integer
      handler->compare_function = def_comparefunction;
   } else {
      handler->compare_function = compare_function;
   }

   if (!dump_function) {
      handler->dump_function = def_dumpfunction;
   } else {
      handler->dump_function = dump_function;
   }

   // need an array of pointers for hashtable. Pointers holding
   // head of linked list
   hashtable = (void **)malloc(num_buckets * (sizeof(unsint32_t *)));
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

void myprint()
{
    printf("hello world\n");
}


