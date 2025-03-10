#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ds/dyrray.h"
#include "utils.h"

#define DYRRAYNULL                                                             \
    (dyrray) { 0, 0, 0, NULL }

typedef enum { LEFT, RIGHT } shift_type;

static inline void _shift(dyrray *dr, size_t init, size_t end, shift_type st) {
    char *base = dr->data;

    if (st == LEFT) {
        memmove(base + dr->item_size * (init - 1), base + dr->item_size * init,
                (end - init + 1) * dr->item_size);
    } else {
        memmove(base + dr->item_size * (init + 1), base + dr->item_size * init,
                (end - init + 1) * dr->item_size);
    }
}

bool dyrray_init(dyrray *dr, size_t item_size, size_t initial_capacity) {
    if (dr == NULL) {
        return false;
    }

    *dr = (dyrray){initial_capacity, item_size, 0,
                   malloc(item_size * initial_capacity)};

    if (dr->data == NULL) {
        *dr = DYRRAYNULL;
        return false;
    }

    return true;
}

void *dyrray_get(dyrray *dr, size_t index) {
    if (dr == NULL || dr->size == 0 || index >= dr->size) {
        return NULL;
    }

    return (char *)dr->data + dr->item_size * index;
}

bool dyrray_insert(dyrray *dr, void *item, size_t index) {
    if (dr == NULL || item == NULL || index > dr->size) {
        return false;
    }

    if (index == dr->size) {
        return dyrray_push(dr, item);
    } else {
        if (dr->size >= dr->capacity) {
            dr->capacity *= 2;

            if (dr->capacity == 0) {
                dr->capacity = DYRRAY_DEFAULT_CAPACITY;
            }

            dr->data = realloc(dr->data, dr->item_size * dr->capacity);

            if (dr->data == NULL) {
                return false;
            }
        }

        _shift(dr, index, dr->size - 1, RIGHT);
        memcpy((char *)dr->data + dr->item_size * index, item, dr->item_size);
        dr->size++;
    }

    return true;
}

bool dyrray_delete(dyrray *dr, size_t index) {
    if (dr == NULL || index >= dr->size) {
        return false;
    }

    if (index == dr->size - 1) {
        return dyrray_pop(dr);
    } else {
        _shift(dr, index + 1, dr->size, LEFT);
        dr->size--;
    }

    return true;
}

bool dyrray_push(dyrray *dr, void *item) {
    if (dr == NULL || item == NULL) {
        return false;
    }

    if (dr->size >= dr->capacity) {
        dr->capacity *= 2;

        if (dr->capacity == 0) {
            dr->capacity = DYRRAY_DEFAULT_CAPACITY;
        }

        dr->data = realloc(dr->data, dr->item_size * dr->capacity);

        if (dr->data == NULL) {
            return false;
        }
    }

    memcpy((char *)dr->data + dr->item_size * dr->size++, item, dr->item_size);

    return true;
}

bool dyrray_pop(dyrray *dr) {
    if (dr == NULL || dr->size == 0) {
        return false;
    }

    dr->size--;
    return true;
}

bool dyrray_swap(dyrray *dr, size_t first_index, size_t second_index) {
    if (dr == NULL || first_index > dr->size || second_index > dr->size) {
        return false;
    }

    char *base = dr->data;
    ut_swap(base + dr->item_size * first_index,
            base + dr->item_size * second_index, dr->item_size);
    return true;
}

void dyrray_destroy(dyrray *dr) {
    if (dr == NULL) {
        return;
    }

    free(dr->data);
    *dr = DYRRAYNULL;
}
