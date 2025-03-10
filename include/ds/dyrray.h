#ifndef DYRRAY_H
#define DYRRAY_H

#include <stdbool.h>
#include <stddef.h>

#define DYRRAY_DEFAULT_CAPACITY 10

typedef struct {
    size_t capacity;
    size_t item_size;
    size_t size;
    void *data;
} dyrray;

bool dyrray_init(dyrray *dr, size_t item_size, size_t initial_capacity);

bool dyrray_push(dyrray *dr, void *item);
bool dyrray_insert(dyrray *dr, void *item, size_t index);

bool dyrray_pop(dyrray *dr);
bool dyrray_delete(dyrray *dr, size_t index);

void *dyrray_get(dyrray *dr, size_t index);
bool dyrray_swap(dyrray *dr, size_t first_index, size_t second_index);

void dyrray_destroy(dyrray *dr);

#endif
