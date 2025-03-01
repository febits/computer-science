#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node {
    struct node *next;
    void *data;
} stack_node;

typedef struct {
    stack_node *top;
    size_t size;
} stack;

bool stack_init(stack *s);

stack_node *stack_peek(stack *s);
bool stack_isempty(stack *s);
bool stack_push(stack *s, void *data);
bool stack_pop(stack *s);
void stack_destroy(stack *s);

#endif
