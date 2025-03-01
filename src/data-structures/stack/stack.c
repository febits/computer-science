#include <stdio.h>
#include <stdlib.h>

#include "ds/stack.h"
#include "types.h"
#include "utils.h"

bool stack_init(stack *s) {
    if (s == NULL) {
        return false;
    }

    *s = (stack){NULL, 0};
    return true;
}
bool stack_isempty(stack *s) { return s->size == 0; }

static stack_node *_create_node(void *data) {
    stack_node *nnode = malloc(sizeof(stack_node));

    if (nnode == NULL) {
        return NULL;
    }

    nnode->data = data;
    nnode->next = NULL;

    return nnode;
}

stack_node *stack_peek(stack *s) {
    if (s == NULL) {
        return NULL;
    }

    return s->top;
}

bool stack_push(stack *s, void *data) {
    if (s == NULL) {
        return false;
    }

    stack_node *nnode = _create_node(data);

    if (nnode == NULL) {
        return false;
    }

    if (s->top == NULL) {
        s->top = nnode;
    } else {
        nnode->next = s->top;
        s->top = nnode;
    }

    s->size++;
    return true;
}

bool stack_pop(stack *s) {
    if (s == NULL || s->size == 0) {
        return false;
    }

    stack_node *fnode = s->top;
    s->top = fnode->next;
    free(fnode);

    s->size--;
    return true;
}

void stack_destroy(stack *s) {
    if (s == NULL) {
        return;
    }

    size_t size = s->size;
    for (size_t i = 0; i < size; i++) {
        stack_pop(s);
    }

    s->top = NULL;
    s->size = 0;
}
