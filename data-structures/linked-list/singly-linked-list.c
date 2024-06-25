#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "utils.h"

#define NOINDEX (-1)

typedef enum { AT_HEAD, AT_TAIL, AT_POSITION, BY_VALUE } op_type;

typedef struct ll_node {
  struct ll_node *next;
  void *data;
} ll_node;

typedef struct {
  ll_node *head;
  size_t size;
} singly_ll;

singly_ll *ll_init(void) {
  singly_ll *ll = malloc(sizeof(singly_ll));
  if (ll == NULL) {
    return NULL;
  }

  ll->head = NULL;
  ll->size = 0;

  return ll;
}

static ll_node *_insert_at_head(singly_ll *ll, ll_node *node) {
  node->next = ll->head;
  ll->head = node;

  ll->size++;
  return node;
}

static ll_node *_insert_at_tail(singly_ll *ll, ll_node *node) {
  ll_node *curr = ll->head;
  for (; curr->next; curr = curr->next) {
    ;
  }

  curr->next = node;

  ll->size++;
  return node;
}

static ll_node *_insert_at_pos(singly_ll *ll, ll_node *node, u64 pos) {
  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (u64 i = 0; i < pos; i++, prev = curr, curr = curr->next) {
    ;
  }

  node->next = curr;
  prev->next = node;

  ll->size++;
  return node;
}

ll_node *insert(singly_ll *ll, void *data, op_type type, i64 pos) {
  ll_node *node = malloc(sizeof(ll_node));

  if (ll == NULL || node == NULL || pos >= (i64)ll->size) {
    return NULL;
  }

  node->data = data;
  node->next = NULL;

  if (type == AT_HEAD && pos <= NOINDEX) {
    return _insert_at_head(ll, node);
  } else if (type == AT_TAIL && pos <= NOINDEX) {
    if (ll->size == 0) {
      return _insert_at_head(ll, node);
    }

    return _insert_at_tail(ll, node);
  } else if (type == AT_POSITION && pos > NOINDEX) {
    if (pos == 0 || pos == (i64)ll->size - 1) {
      switch (pos) {
        case 0: return _insert_at_head(ll, node); break;
        default: return _insert_at_tail(ll, node);
      }
    }

    return _insert_at_pos(ll, node, pos);
  }

  return NULL;
}

static ll_node *_delete_at_head(singly_ll *ll) {
  ll_node *tmp = ll->head;
  ll->head = ll->head->next;

  ll->size--;
  return tmp;
}

static ll_node *_delete_at_tail(singly_ll *ll) {
  ll_node *tmp = NULL;

  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (; curr->next; prev = curr, curr = curr->next) {
    ;
  }

  tmp = curr;
  prev->next = NULL;

  ll->size--;
  return tmp;
}

static ll_node *_delete_at_position(singly_ll *ll, u64 pos) {
  ll_node *tmp = NULL;

  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (u64 i = 0; i < pos; i++, prev = curr, curr = curr->next) {
    ;
  }

  tmp = curr;
  prev->next = curr->next;
  
  ll->size--;
  return tmp;
}

static ll_node *_delete_by_value(singly_ll *ll, void *data) {
  ll_node *tmp = NULL;

  ll_node *prev = NULL;
  ll_node *curr = ll->head;

  for (; curr; prev = curr, curr = curr->next) {
    if ((u64)curr->data == (u64)data) {
      tmp = curr;
      prev->next = curr->next;
      break;
    }
  }

  ll->size--;
  return tmp;
}

ll_node *delete(singly_ll *ll, void *data, op_type type, i64 pos) {
  if (ll == NULL || ll->head == NULL || pos >= (i64)ll->size) {
    return NULL;
  }

  if (type == AT_HEAD && pos <= NOINDEX) {
    return _delete_at_head(ll);
  } else if (type == AT_TAIL && pos <= NOINDEX) {
    if (ll->size == 1) {
      return _delete_at_head(ll);
    }

    return _delete_at_tail(ll);
  } else if (type == BY_VALUE && pos <= NOINDEX) {
    if (data == NULL) {
      return NULL;
    }

    return _delete_by_value(ll, data);
  } else if (type == AT_POSITION && pos > NOINDEX) {
    if (pos == 0 || pos == (i64)ll->size - 1) {
      switch (pos) {
        case 0: return _delete_at_head(ll); break;
        default: return _delete_at_tail(ll);
      }
    }

    return _delete_at_position(ll, pos);
  }

  return NULL;
}

ll_node *search(singly_ll *ll, void *data) {
  if (ll == NULL) {
    return NULL;
  }

  for (ll_node *curr = ll->head; curr; curr = curr->next) {
    if ((u64)curr->data == (u64)data) {
      return curr;
    }
  }

  return NULL;
}

ll_node *get(singly_ll *ll, u64 pos) {
  if (ll == NULL || pos >= ll->size) {
    return NULL;
  }

  ll_node *curr = ll->head;
  for (u64 i = 0; i < pos; i++, curr = curr->next) {
    ;
  }

  return curr;
}

void display(singly_ll *ll) {
  if (ll == NULL || ll->size == 0) {
    return;
  }

  ll_node *curr = ll->head;

  printf("\n");
  for (u64 i = 0; curr; curr = curr->next, i++) {
    printf(" %lu%s", (u64)curr->data, i != ll->size - 1 ? " ->" : "");
  }
  printf("\n\n");
}

void destroy(singly_ll *ll) {
  if (ll == NULL) {
    return;
  }

  size_t sz = ll->size;
  for (size_t i = 0; i < sz; i++) {
    free(delete (ll, NULL, AT_HEAD, -1));
  }

  free(ll);
}

int main(void) {
  u64 arr[] = {50, 120, 500, 1000, 5000, 1e4};
  ut_print_array(arr, ARRSIZE(arr));

  singly_ll *ll = ll_init();
  if (ll == NULL) {
    error("couldn't allocate stack structure: malloc()\n");
  }

  for (size_t i = 0; i < ARRSIZE(arr); i++) {
    if (insert(ll, (void *)arr[i], AT_HEAD, NOINDEX)) {
      printf("Adding at head: %lu\n", arr[i]);
    }
  }

  display(ll);

  if (insert(ll, (void *)15, AT_TAIL, NOINDEX)) {
    printf("Adding at tail: %d\n", 15);
    display(ll);
  }

  if (insert(ll, (void *)2000, AT_POSITION, 3)) {
    printf("Adding at position(3): %d\n", 2000);
    display(ll);
  }

  if (insert(ll, (void *)8500, AT_POSITION, 5)) {
    printf("Adding at position(5): %d\n", 8500);
    display(ll);
  }

  ll_node *tmp = delete (ll, NULL, AT_HEAD, NOINDEX);
  if (tmp) {
    printf("Deleting at head: %lu\n", (u64)tmp->data);
    display(ll);
    free(tmp);
  }

  tmp = delete (ll, NULL, AT_TAIL, NOINDEX);
  if (tmp) {
    printf("Deleting at tail: %lu\n", (u64)tmp->data);
    display(ll);
    free(tmp);
  }

  tmp = delete(ll, NULL, AT_POSITION, 2);
  if (tmp) {
    printf("Deleting at position(2): %lu\n", (u64)tmp->data);
    display(ll);
    free(tmp);
  }

  tmp = delete(ll, (void *)8500, BY_VALUE, NOINDEX);
  if (tmp) {
    printf("Deleting by value: %lu\n", (u64)tmp->data);
    display(ll);
    free(tmp);
  }

  tmp = search(ll, (void *)5000);
  if (tmp) {
    printf("Searching %lu... Found it!\n", (u64)tmp->data);
  }

  tmp = get(ll, 4);
  if (tmp) {
    printf("Getting %lu... Got it!\n", (u64)tmp->data);
  }

  destroy(ll);
}
