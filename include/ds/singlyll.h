#ifndef SINGLYLL_H
#define SINGLYLL_H

#include <stdbool.h>
#include <stddef.h>

#include "utils.h"

typedef struct ll_node {
    struct ll_node *next;
    void *data;
} ll_node;

typedef struct {
    ll_node *head;
    size_t size;
} singly_ll;

bool ll_init(singly_ll *ll);

bool ll_insert_at_head(singly_ll *ll, void *data);
bool ll_insert_at_tail(singly_ll *ll, void *data);
bool ll_insert_at_pos(singly_ll *ll, void *data, size_t pos);

bool ll_delete_at_head(singly_ll *ll);
bool ll_delete_at_tail(singly_ll *ll);
bool ll_delete_at_pos(singly_ll *ll, size_t pos);
bool ll_delete_by_value(singly_ll *ll, void *data, compare *cmp);

ll_node *ll_search(singly_ll *ll, void *data, compare *cmp);
ll_node *ll_get(singly_ll *ll, size_t pos);

bool ll_isempty(singly_ll *ll);

void ll_destroy(singly_ll *ll);

#endif
