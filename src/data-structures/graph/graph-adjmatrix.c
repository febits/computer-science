#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds/graphm.h"

void graphm_destroy(graphm *g) {
    if (g == NULL) {
        return;
    }

    for (size_t i = 0; i < g->vertices; i++) {
        free(g->adjmatrix[i]);
    }

    free(g->adjmatrix);
}

graphm graphm_init(size_t vertices_num) {
    graphm g = {NULL, vertices_num};

    g.adjmatrix = calloc(g.vertices, sizeof(bool *));
    if (g.adjmatrix == NULL) {
        return (graphm){NULL, 0};
    }

    for (size_t i = 0; i < g.vertices; i++) {
        g.adjmatrix[i] = calloc(g.vertices, sizeof(bool));
        if (g.adjmatrix[i] == NULL) {
            graphm_destroy(&g);
            return (graphm){NULL, 0};
        }
    }

    return g;
}

bool graphm_add_edge(graphm *g, size_t from, size_t to) {
    if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
        to >= g->vertices) {
        return false;
    }

    g->adjmatrix[from][to] = true;
    return true;
}

bool graphm_is_edge(graphm *g, size_t from, size_t to) {
    if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
        to >= g->vertices || g->adjmatrix[from][to] == false) {
        return false;
    }

    return true;
}

bool graphm_delete_edge(graphm *g, size_t from, size_t to) {
    if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
        to >= g->vertices) {
        return false;
    }

    g->adjmatrix[from][to] = false;
    return true;
}
