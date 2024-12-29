#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct queue_node {
    struct queue_node *next;
    void *data;
} queue_node;

typedef struct {
    queue_node *front;
    queue_node *rear;
    size_t size;
} queue;

queue queue_init(void);

queue_node *q_front(queue *q);
bool q_isempty(queue *q);
bool q_enqueue(queue *q, void *data);
bool q_dequeue(queue *q);
void q_destroy(queue *q);

#endif
