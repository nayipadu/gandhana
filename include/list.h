#ifndef LIST_H
#define LIST_H
#include <common.h>

typedef struct node {
    void* data;
    struct node* next;
}node_t;

typedef struct list_head {
    node_t *node;
    unsigned int count;
}list_head_t;

typedef int (*compare_fn_t) (voidp key, voidp comparewith);
int SLIST_INSERT_AT_HEAD(list_head_t *lh, voidp data);
voidp SLIST_LOOKUP(list_head_t *lh, compare_fn_t comp_fn, voidp key);

#endif /* LIST_H */
