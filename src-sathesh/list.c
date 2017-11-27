#include <stdlib.h>
#include "list.h"

#define LIST_MALLOC malloc
#define LIST_FREE free

int SLIST_INSERT_AT_HEAD(list_head_t *lh, voidp data)
{
    node_t *node = LIST_MALLOC(sizeof(node_t));
    if (!node)
        return -1;

    node->data = data;
    node->next = lh->node;
    lh->node = node;
    lh->count++;
    return 0;
}

voidp SLIST_LOOKUP(list_head_t *lh, compare_fn_t comp_fn, voidp key)
{
    node_t *node = lh->node;

    while(node) {
        if (comp_fn(key, node->data) == 0)
            return node->data;
        node = node->next;
    }
    return NULL;
}
