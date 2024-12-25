#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

typedef struct {
  bool **adjmatrix;
  u64 vertices;
} graph;

void destroy(graph *g) {
  if (g == NULL) {
    return;
  }

  for (size_t i = 0; i < g->vertices; i++) {
    free(g->adjmatrix[i]);
  }

  free(g->adjmatrix);
  free(g);
}

graph *graph_init(u64 vertices) {
  graph *g = malloc(sizeof(graph));
  if (g == NULL) return NULL;

  g->vertices = vertices;
  g->adjmatrix = calloc(g->vertices, sizeof(bool *));
  if (g->adjmatrix == NULL) {
    free(g);
    return NULL;
  }

  for (size_t i = 0; i < g->vertices; i++) {
    g->adjmatrix[i] = calloc(g->vertices, sizeof(bool));
    if (g->adjmatrix[i] == NULL) {
      destroy(g);
      return NULL;
    }
  }

  return g;
}

bool add_edge(graph *g, u64 from, u64 to) {
  if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
      to >= g->vertices) {
    return false;
  }

  g->adjmatrix[from][to] = true;
  return true;
}

bool is_edge(graph *g, u64 from, u64 to) {
  if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
      to >= g->vertices || g->adjmatrix[from][to] == false) {
    return false;
  }

  return true;
}

bool delete_edge(graph *g, u64 from, u64 to) {
  if (g == NULL || g->adjmatrix == NULL || from >= g->vertices ||
      to >= g->vertices) {
    return false;
  }

  g->adjmatrix[from][to] = false;
  return true;
}

void display(graph *g) {
  if (g == NULL) {
    return;
  }

  printf("\n");
  for (size_t i = 0; i < g->vertices; i++) {
    printf(" %lu | ", i);
    for (size_t j = 0; j < g->vertices; j++) {
      printf("%-3u", g->adjmatrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

bool gendotfile(graph *g, const char *filename) {
  FILE *f = fopen(filename, "w");
  if (f == NULL) return false;

  fprintf(f, "digraph G {\n");
  fprintf(f, "\tnode [shape=circle];\n");
  for (size_t i = 0; i < g->vertices; i++) {
    for (size_t j = 0; j < g->vertices; j++) {
      if (is_edge(g, i, j)) {
        fprintf(f, "\t%lu -> %lu\n", i, j);
      }
    }
  }
  fprintf(f, "}\n");

  fclose(f);
  return true;
}
