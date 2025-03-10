#ifndef GRAPHM_H
#define GRAPHM_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    bool **adjmatrix;
    size_t vertices;
} graphm;

bool graphm_init(graphm *g, size_t verticies_num);

bool graphm_add_edge(graphm *g, size_t from, size_t to);
bool graphm_is_edge(graphm *g, size_t from, size_t to);
bool graphm_delete_edge(graphm *g, size_t from, size_t to);

void graphm_destroy(graphm *g);

#endif
