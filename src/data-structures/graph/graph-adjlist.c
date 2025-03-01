#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds/graphl.h"

#define GRAPHNULL (graphl){NULL, 0}

bool graphl_init(graphl *g, size_t vertices_num) {
    if (g == NULL) {
        return false;
    }

    *g = (graphl){NULL, vertices_num};

    g->adjlist = calloc(g->vertices, sizeof(adjlist_node *));
    if (g->adjlist == NULL) {
        *g = GRAPHNULL;
        return false;
    }

    return true;
}

static adjlist_node *create_node(int vertex) {
    adjlist_node *node = malloc(sizeof(adjlist_node));
    if (node == NULL) {
        return NULL;
    }

    node->vertex = vertex;
    node->next = NULL;

    return node;
}

bool graphl_add_edge(graphl *g, size_t from, size_t to) {
    if (g == NULL || g->adjlist == NULL || from >= g->vertices ||
        to >= g->vertices) {
        return false;
    }

    adjlist_node *node = create_node(to);

    if (node == NULL) {
        return false;
    }

    node->next = g->adjlist[from];
    g->adjlist[from] = node;

    return true;
}

bool graphl_is_edge(graphl *g, size_t from, size_t to) {
    if (g == NULL || g->adjlist == NULL || from >= g->vertices ||
        to >= g->vertices) {
        return false;
    }

    for (adjlist_node *curr = g->adjlist[from]; curr; curr = curr->next) {
        if (curr->vertex == (int)to) {
            return true;
        }
    }

    return false;
}

void graphl_destroy(graphl *g) {
    if (g == NULL) {
        return;
    }

    for (size_t i = 0; i < g->vertices; i++) {
        adjlist_node *tmp = NULL;
        adjlist_node *curr = g->adjlist[i];
        while (curr) {
            tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }

    free(g->adjlist);
}
