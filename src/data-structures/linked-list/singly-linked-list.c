#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "singlyll.h"
#include "types.h"

singly_ll ll_init(void) { return (singly_ll){NULL, 0}; }
bool ll_isempty(singly_ll *ll) { return ll->size == 0; }

static ll_node *_create_node(void *data) {
    ll_node *nnode = malloc(sizeof(ll_node));

    if (nnode == NULL) {
        return NULL;
    }

    nnode->data = data;
    nnode->next = NULL;

    return nnode;
}

bool ll_insert_at_head(singly_ll *ll, void *data) {
    if (ll == NULL || data == NULL) {
        return false;
    }

    ll_node *nnode = _create_node(data);

    if (nnode == NULL) {
        return false;
    }

    if (ll->head == NULL) {
        ll->head = nnode;
    } else {
        nnode->next = ll->head;
        ll->head = nnode;
    }

    ll->size++;
    return true;
}

bool ll_insert_at_tail(singly_ll *ll, void *data) {
    if (ll == NULL || data == NULL) {
        return false;
    }

    ll_node *nnode = _create_node(data);

    if (nnode == NULL) {
        return false;
    }

    if (ll->head == NULL) {
        ll->head = nnode;
    } else {
        ll_node *tnode = ll->head;
        while (tnode->next != NULL) {
            tnode = tnode->next;
        }

        tnode->next = nnode;
    }

    ll->size++;
    return true;
}

bool ll_insert_at_pos(singly_ll *ll, void *data, size_t pos) {
    if (ll == NULL || data == NULL) {
        return false;
    }

    if (pos != 0 && ll->size != 0) {
        if (pos >= ll->size) {
            return false;
        }
    }

    ll_node *nnode = _create_node(data);

    if (nnode == NULL) {
        return false;
    }

    if (pos == 0) {
        free(nnode);
        return ll_insert_at_head(ll, data);
    } else {
        ll_node *tnode = ll->head;

        for (size_t i = 0; i < pos - 1; i++) {
            tnode = tnode->next;
        }

        if (tnode == NULL) {
            free(nnode);
            return false;
        }

        nnode->next = tnode->next;
        tnode->next = nnode;
    }

    ll->size++;
    return true;
}

bool ll_delete_at_head(singly_ll *ll) {
    if (ll == NULL || ll->head == NULL) {
        return false;
    }

    ll_node *tnode = ll->head;
    ll->head = ll->head->next;
    free(tnode);

    ll->size--;
    return true;
}

bool ll_delete_at_tail(singly_ll *ll) {
    if (ll == NULL || ll->head == NULL) {
        return false;
    }

    if (ll->size == 1) {
        return ll_delete_at_head(ll);
    } else {
        ll_node *tnode = ll->head;
        while (tnode->next->next != NULL) {
            tnode = tnode->next;
        }

        free(tnode->next);
        tnode->next = NULL;
    }

    ll->size--;
    return true;
}

bool ll_delete_at_pos(singly_ll *ll, size_t pos) {
    if (ll == NULL || ll->head == NULL || pos >= ll->size) {
        return false;
    }

    if (pos == 0) {
        ll_node *tnode = ll->head;
        ll->head = ll->head->next;
        free(tnode);
    } else {
        ll_node *tnode = ll->head;
        ll_node *fnode = NULL;
        for (size_t i = 0; i < pos - 1; i++) {
            tnode = tnode->next;
        }

        fnode = tnode->next;
        tnode->next = fnode->next;
        free(fnode);
    }

    ll->size--;
    return true;
}

bool ll_delete_by_value(singly_ll *ll, void *data, compare *cmp) {
    if (ll == NULL || ll->head == NULL || data == NULL || cmp == NULL) {
        return false;
    }

    if (cmp(data, ll->head->data) == 0) {
        ll_node *tnode = ll->head;
        ll->head = ll->head->next;
        free(tnode);

        ll->size--;
        return true;
    } else {
        ll_node *tnode = ll->head;
        while (tnode->next != NULL) {
            if (cmp(data, tnode->next->data) == 0) {
                ll_node *fnode = tnode->next;
                tnode->next = fnode->next;
                free(fnode);

                ll->size--;
                return true;
            }

            tnode = tnode->next;
        }
    }

    return false;
}

ll_node *ll_search(singly_ll *ll, void *data, compare *cmp) {
    if (ll == NULL || ll->head == NULL || data == NULL || cmp == NULL) {
        return NULL;
    }

    ll_node *tnode = ll->head;
    while (tnode != NULL) {
        if (cmp(data, tnode->data) == 0) {
            return tnode;
        }
        tnode = tnode->next;
    }

    return NULL;
}

ll_node *ll_get(singly_ll *ll, size_t pos) {
    if (ll == NULL || ll->head == NULL || pos >= ll->size) {
        return NULL;
    }

    ll_node *tnode = ll->head;
    for (size_t i = 0; i < pos; i++) {
        tnode = tnode->next;
    }

    return tnode;
}

void ll_destroy(singly_ll *ll) {
    if (ll == NULL) {
        return;
    }

    ll_node *tnode = ll->head;
    ll_node *fnode = NULL;
    while (tnode != NULL) {
        fnode = tnode;
        tnode = tnode->next;
        free(fnode);
    }

    ll->head = NULL;
}
