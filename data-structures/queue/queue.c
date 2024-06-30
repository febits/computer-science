#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

typedef struct queue_node {
  struct queue_node *next;
  void *data;
} queue_node;

typedef struct {
  queue_node *front;
  queue_node *rear;
  size_t size;
} queue;

queue *queue_init(void) {
  queue *q = malloc(sizeof(queue));
  if (q == NULL) {
    return NULL;
  }

  q->front = NULL;
  q->rear = NULL;
  q->size = 0;

  return q;
}

queue_node *enqueue(queue *q, void *data) {
  queue_node *node = malloc(sizeof(queue_node));
  if (q == NULL || node == NULL) {
    return NULL;
  }

  node->data = data;
  node->next = NULL;

  if (q->front == NULL) {
    q->front = node;
    q->rear = node;
  } else {
    q->rear->next = node;
    q->rear = node;
  }

  q->size++;
  return node;
}

queue_node *dequeue(queue *q) {
  if (q == NULL) {
    return NULL;
  }

  queue_node *node = q->front;
  q->front = node->next;

  q->size--;
  return node;
}

queue_node *front(queue *q) {
  if (q == NULL) {
    return NULL;
  }

  return q->front;
}

void display(queue *q) {
  if (q == NULL) {
    return;
  }

  printf("\n");
  queue_node *curr = q->front;

  for (u64 i = 0; curr; curr = curr->next, i++) {
    printf(" %lu%s", (u64)curr->data, i != q->size - 1 ? " <-" : "");
  }
  printf("\n\n");
}

void destroy(queue *q) {
  if (q == NULL) {
    return;
  }

  size_t sz = q->size;
  for (size_t i = 0; i < sz; i++) {
    free(dequeue(q));
  }

  free(q);
}

int main(void) {
  u64 arr[] = {20, 35, 100, 1000, 550, 965};
  ut_print_array(arr, ARRSIZE(arr));

  queue *q = queue_init();
  if (q == NULL) {
    error("couldn't allocate queue structure: malloc()\n");
  }

  for (size_t i = 0; i < ARRSIZE(arr); i++) {
    if (enqueue(q, (void *)arr[i])) {
      printf("Adding %lu\n", arr[i]);
    }
  }

  display(q);

  printf("Front: %lu\n\n", (u64)front(q)->data);

  queue_node *tmp = dequeue(q);
  if (tmp) {
    printf("Dequeuing %lu...\n", (u64)tmp->data);
    free(tmp);
  }

  display(q);

  printf("Front: %lu\n\n", (u64)front(q)->data);

  destroy(q);

  return EXIT_SUCCESS;
}
