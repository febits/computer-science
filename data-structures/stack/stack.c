#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

typedef struct node {
  struct node *next;
  void *data;
} stack_node;

typedef struct {
  stack_node *top;
  size_t size;
} stack;

stack *stack_init(void) {
  stack *stk = malloc(sizeof(stack));
  if (stk == NULL) {
    return NULL;
  }

  stk->top = NULL;
  stk->size = 0;

  return stk;
}

stack_node *push(stack *stk, void *data) {
  stack_node *node = malloc(sizeof(stack_node));

  if (stk == NULL || node == NULL) {
    return NULL;
  }

  node->data = data;
  node->next = NULL;

  if (stk->top == NULL) {
    stk->top = node;
  } else {
    node->next = stk->top;
    stk->top = node;
  }

  stk->size++;
  return node;
}

stack_node *pop(stack *stk) {
  if (stk == NULL || stk->top == NULL) {
    return NULL;
  }

  stack_node *node = stk->top;
  stk->top = node->next;

  stk->size--;
  return node;
}

stack_node *peek(stack *stk) {
  if (stk == NULL) {
    return NULL;
  }

  return stk->top;
}

void display(stack *stk) {
  if (stk == NULL) {
    return;
  }

  printf("\n");
  stack_node *curr = stk->top;

  for (u8 i = 0; curr; curr = curr->next, i++) {
    printf(" %lu%s\n", (u64)curr->data, i == 0 ? " <- TOP" : "");
  }
  printf("\n");
}

void destroy(stack *stk) {
  if (stk == NULL) {
    return;
  }

  size_t sz = stk->size;
  for (size_t i = 0; i < sz; i++) {
    free(pop(stk));
  }

  free(stk);
}

int main(void) {
  u64 arr[] = {10, 20, 30, 50, 80, 100};
  ut_print_array(arr, ARRSIZE(arr));

  stack *stk = stack_init();
  if (stk == NULL) {
    error("couldn't allocate stack structure: malloc()\n");
  }

  for (size_t i = 0; i < ARRSIZE(arr); i++) {
    if (push(stk, (void *)arr[i])) {
      printf("Adding %lu\n", arr[i]);
    }
  }

  display(stk);

  printf("Peek: %lu\n\n", (u64)peek(stk)->data);

  stack_node *tmp = pop(stk);
  if (tmp) {
    printf("Popping %lu...\n", (u64)tmp->data);
    free(tmp);
  }

  display(stk);
  printf("Peek: %lu\n", (u64)peek(stk)->data);

  destroy(stk);

  return EXIT_SUCCESS;
}
