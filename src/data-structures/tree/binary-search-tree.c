#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

typedef enum { INODER, PREORDER, POSTORDER } traversal_type;

typedef struct bst_node {
  struct bst_node *left, *right;
  u64 value;
} bst_node;

bst_node *find_min(bst_node *root) {
  if (root == NULL) {
    return NULL;
  }

  bst_node *curr = root;
  while (curr->left) {
    curr = curr->left;
  }

  return curr;
}

bst_node *find_max(bst_node *root) {
  if (root == NULL) {
    return NULL;
  }

  bst_node *curr = root;
  while (curr->right) {
    curr = curr->right;
  }

  return curr;
}

u64 find_height(bst_node *root) {
  if (root == NULL) {
    return 0;
  }

  u64 left = find_height(root->left);
  u64 right = find_height(root->right);

  return (left > right ? left : right) + 1;
}

u64 find_nodes_num(bst_node *root) {
  if (root == NULL) {
    return 0;
  }

  return find_nodes_num(root->left) + find_nodes_num(root->right) + 1;
}

bst_node *insert(bst_node **root, u64 value) {
  bst_node *node = malloc(sizeof(bst_node));
  if (node == NULL) return NULL;

  node->left = node->right = NULL;
  node->value = value;

  if (*root == NULL) {
    *root = node;
  } else {
    bst_node *parent = NULL;
    bst_node *curr = *root;

    while (curr) {
      parent = curr;

      if (value <= curr->value) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    if (value <= parent->value) {
      parent->left = node;
    } else {
      parent->right = node;
    }
  }

  return node;
}

bst_node *delete(bst_node **root, u64 value) {
  bst_node *parent = NULL;
  bst_node *curr = *root;

  while (curr && curr->value != value) {
    parent = curr;
    if (value < curr->value) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  if (curr == NULL) return NULL;

  if (curr->left == NULL && curr->right == NULL) {
    if (curr != *root) {
      if (parent->left == NULL) {
        parent->left = NULL;
      } else {
        parent->right = NULL;
      }
    } else {
      *root = NULL;
    }
  } else if (curr->left && curr->right) {
    bst_node *predecessor = find_min(curr->right);
    curr->value = predecessor->value;
    return delete (&curr->right, predecessor->value);
  } else {
    bst_node *child = curr->left ? curr->left : curr->right;

    if (curr != *root) {
      if (curr == parent->left) {
        parent->left = child;
      } else {
        parent->right = child;
      }
    } else {
      *root = child;
    }
  }

  return curr;
}

bst_node *search(bst_node *root, u64 value) {
  if (root == NULL) {
    return NULL;
  }

  bst_node *curr = root;
  while (curr) {
    if (curr->value == value) {
      return curr;
    } else if (value < curr->value) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  return NULL;
}

static void _inorder(bst_node *root) {
  if (root) {
    _inorder(root->left);
    printf("%lu ", root->value);
    _inorder(root->right);
  }
}
static void _preorder(bst_node *root) {
  if (root) {
    printf("%lu ", root->value);
    _preorder(root->left);
    _preorder(root->right);
  }
}
static void _postorder(bst_node *root) {
  if (root) {
    _postorder(root->left);
    _postorder(root->right);
    printf("%lu ", root->value);
  }
}

void traversal(bst_node *root, traversal_type type) {
  printf("\n");
  switch (type) {
    case INODER:
      printf("Inorder: ");
      _inorder(root);
      break;
    case PREORDER:
      printf("Preorder: ");
      _preorder(root);
      break;
    case POSTORDER:
      printf("Postorder: ");
      _postorder(root);
      break;
  }
}

void gennodes(bst_node *root, FILE *file) {
  if (root) {
    if (root->left) {
      fprintf(file, "\t%lu -> %lu;\n", root->value, root->left->value);
      gennodes(root->left, file);
    }
    if (root->right) {
      fprintf(file, "\t%lu -> %lu;\n", root->value, root->right->value);
      gennodes(root->right, file);
    }
  }
}

bool gendotfile(bst_node *root, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) return false;

  fprintf(file, "digraph Tree {\n");
  fprintf(file, "node [shape=circle];\n");
  gennodes(root, file);
  fprintf(file, "}\n");

  fclose(file);
  return true;
}

void destroy(bst_node *root) {
  if (root) {
    destroy(root->left);
    destroy(root->right);
    free(root);
  }
}
