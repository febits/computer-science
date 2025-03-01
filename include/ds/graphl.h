#ifndef GRAPHL_H
#define GRAPHL_H

#include <stdbool.h>
#include <stddef.h>

typedef struct adjlist_node {
    struct adjlist_node *next;
    int vertex;
} adjlist_node;

typedef struct {
    adjlist_node **adjlist;
    size_t vertices;
} graphl;

bool graphl_init(graphl *g, size_t vertices_num);
bool graphl_add_edge(graphl *g, size_t from, size_t to);
bool graphl_is_edge(graphl *g, size_t from, size_t to);
void graphl_destroy(graphl *g);

#endif
