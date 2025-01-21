#ifndef BST_H
#define BST_H

#include <stdbool.h>

#include "utils.h"

typedef struct bst_node {
    struct bst_node *left, *right;
    void *data;
} bst_node;

bool bst_insert(bst_node **root, void *data, compare *cmp);
bool bst_delete(bst_node **root, void *data, compare *cmp);
bst_node *bst_search(bst_node *root, void *data, compare *cmp);

bst_node *bst_max(bst_node *root);
bst_node *bst_min(bst_node *root);
size_t bst_size(bst_node *root);
size_t bst_height(bst_node *root);

void bst_destroy(bst_node **root);

#endif
