#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

bst_node *bst_max(bst_node *root) {
    if (root == NULL) {
        return NULL;
    }

    bst_node *curr = root;
    while (curr->right) {
        curr = curr->right;
    }

    return curr;
}

bst_node *bst_min(bst_node *root) {
    if (root == NULL) {
        return NULL;
    }

    bst_node *curr = root;
    while (curr->left) {
        curr = curr->left;
    }

    return curr;
}

size_t bst_height(bst_node *root) {
    if (root == NULL) {
        return 0;
    }

    size_t left = bst_height(root->left);
    size_t right = bst_height(root->right);

    return (left > right ? left : right) + 1;
}

size_t bst_size(bst_node *root) {
    if (root == NULL) {
        return 0;
    }

    return bst_size(root->left) + bst_size(root->right) + 1;
}

static bst_node *_create_node(void *data) {
    bst_node *nnode = malloc(sizeof(bst_node));

    if (nnode == NULL) {
        return NULL;
    }

    nnode->data = data;
    nnode->left = nnode->right = NULL;

    return nnode;
}

bool bst_insert(bst_node **root, void *data, compare *cmp) {
    if (data == NULL || cmp == NULL) {
        return false;
    }

    bst_node *nnode = _create_node(data);

    if (nnode == NULL) {
        return false;
    }

    if (*root == NULL) {
        *root = nnode;
    } else {
        bst_node *parent = NULL;
        bst_node *curr = *root;

        while (curr) {
            parent = curr;

            if (cmp(data, curr->data) < 0 || cmp(data, curr->data) == 0) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        if (cmp(data, parent->data) < 0 || cmp(data, parent->data) == 0) {
            parent->left = nnode;
        } else {
            parent->right = nnode;
        }
    }

    return true;
}

bool bst_delete(bst_node **root, void *data, compare *cmp) {
    if (*root == NULL || data == NULL || cmp == NULL) {
        return false;
    }

    bst_node *parent = NULL;
    bst_node *curr = *root;

    while (curr && cmp(data, curr->data) != 0) {
        parent = curr;
        if (cmp(data, curr->data) < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (curr == NULL) {
        return false;
    }

    if (curr->left == NULL && curr->right == NULL) {
        if (curr != *root) {
            if (curr == parent->left) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
            free(curr);
        } else {
            free(*root);
            *root = NULL;
        }
    } else if (curr->left && curr->right) {
        bst_node *successor = bst_min(curr->right);
        curr->data = successor->data;
        return bst_delete(&curr->right, successor->data, cmp);
    } else {
        bst_node *child = curr->left ? curr->left : curr->right;

        if (curr != *root) {
            if (curr == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            *root = child;
        }

        free(curr);
    }

    return true;
}

bst_node *bst_search(bst_node *root, void *data, compare *cmp) {
    if (root == NULL || data == NULL || cmp == NULL) {
        return NULL;
    }

    bst_node *curr = root;
    while (curr) {
        if (cmp(data, curr->data) == 0) {
            return curr;
        } else if (cmp(data, curr->data) < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return NULL;
}

static void _destroy_nodes(bst_node *root) {
    if (root) {
        _destroy_nodes(root->left);
        _destroy_nodes(root->right);
        free(root);
    }
}

void bst_destroy(bst_node **root) {
    if (*root == NULL) {
        return;
    }

    _destroy_nodes(*root);
    *root = NULL;
}
