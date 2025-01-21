#include <stdlib.h>

#include "ds/queue.h"
#include "utils.h"

queue queue_init(void) { return (queue){NULL, NULL, 0}; }
bool q_isempty(queue *q) { return q->size == 0; }

static queue_node *_create_node(void *data) {
    queue_node *nnode = malloc(sizeof(queue_node));

    if (nnode == NULL) {
        return NULL;
    }

    nnode->data = data;
    nnode->next = NULL;

    return nnode;
}

queue_node *q_front(queue *q) {
    if (q == NULL) {
        return NULL;
    }

    return q->front;
}

bool q_enqueue(queue *q, void *data) {
    if (q == NULL) {
        return false;
    }

    queue_node *nnode = _create_node(data);

    if (nnode == NULL) {
        return false;
    }

    if (q->front == NULL && q->rear == NULL) {
        q->front = nnode;
        q->rear = nnode;
    } else {
        q->rear->next = nnode;
        q->rear = nnode;
    }

    q->size++;
    return true;
}

bool q_dequeue(queue *q) {
    if (q == NULL || q->size == 0) {
        return false;
    }

    queue_node *fnode = q->front;
    q->front = fnode->next;
    free(fnode);

    q->size--;
    return true;
}

void q_destroy(queue *q) {
    if (q == NULL) {
        return;
    }

    size_t size = q->size;
    for (size_t i = 0; i < size; i++) {
        q_dequeue(q);
    }

    q->rear = q->front = NULL;
    q->size = 0;
}
