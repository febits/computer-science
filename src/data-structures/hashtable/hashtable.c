#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "types.h"
#include "utils.h"

#define FREE_E(he)                                                             \
  free((void *)(he)->key);                                                     \
  free((he));

#define COMPARE(x, y, len) (strncmp((x), (y), (len)) == 0)
#define HASH(h, sz) ((h) % (sz))
#define KEYMAX 1024

typedef u64(hash_fn)(const char *);

typedef struct h_entry {
  struct h_entry *next;
  const char *key;
  void *data;
} h_entry;

typedef struct {
  h_entry **buckets;
  hash_fn *hash;
  size_t capacity;
} htable;

static u64 _djb2(const char *key) {
  u64 hash = 5381;
  char c;

  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

htable *htable_init(size_t sz, hash_fn *hash) {
  htable *ht = malloc(sizeof(htable));
  if (ht == NULL) return NULL;

  ht->buckets = calloc(sz, sizeof(h_entry *));
  if (ht->buckets == NULL) {
    free(ht);
    return NULL;
  }

  ht->hash = hash ? hash : _djb2;
  ht->capacity = sz;

  return ht;
}

static bool _lookup(htable *ht, const char *key) {
  h_entry *curr = ht->buckets[HASH(ht->hash(key), ht->capacity)];

  for (; curr; curr = curr->next) {
    if (COMPARE(curr->key, key, KEYMAX)) {
      return true;
    }
  }

  return false;
}

h_entry *insert(htable *ht, const char *key, void *data) {
  h_entry *he = malloc(sizeof(h_entry));

  if (ht == NULL || he == NULL || key == NULL || _lookup(ht, key)) {
    return NULL;
  }

  he->key = strndup(key, KEYMAX);
  he->data = data;
  he->next = NULL;

  if (he->key == NULL) return NULL;

  u64 index = HASH(ht->hash(he->key), ht->capacity);

  if (ht->buckets[index] == NULL) {
    ht->buckets[index] = he;
  } else {
    he->next = ht->buckets[index];
    ht->buckets[index] = he;
  }

  return he;
}

h_entry *delete(htable *ht, const char *key) {
  if (ht == NULL || key == NULL) {
    return NULL;
  }

  u64 index = HASH(ht->hash(key), ht->capacity);
  h_entry *he = NULL;

  if (ht->buckets[index] != NULL &&
      COMPARE(ht->buckets[index]->key, key, KEYMAX)) {

    he = ht->buckets[index];
    ht->buckets[index] = NULL;
  } else {
    h_entry *prev = NULL;
    h_entry *curr = ht->buckets[index];

    for (; curr; prev = curr, curr = curr->next) {
      if (COMPARE(curr->key, key, KEYMAX)) {
        he = curr;
        prev->next = curr->next;
        break;
      }
    }
  }

  return he;
}

h_entry *get(htable *ht, const char *key) {
  if (ht == NULL || key == NULL) {
    return NULL;
  }

  h_entry *he = NULL;
  u64 index = HASH(ht->hash(key), ht->capacity);

  if (ht->buckets[index]) {
    h_entry *curr = ht->buckets[index];
    for (; curr; curr = curr->next) {
      if (COMPARE(curr->key, key, KEYMAX)) {
        he = curr;
        break;
      }
    }
  }

  return he;
}

void display(htable *ht) {
  if (ht == NULL) {
    return;
  }

  printf("\n");
  for (size_t i = 0; i < ht->capacity; i++) {
    if (ht->buckets[i]) {
      h_entry *curr = ht->buckets[i];
      while (curr) {
        printf(" [slot %lu] -> \"%s\":\t[%p]  (hash=%lu)\n", i, curr->key,
               curr->data, ht->hash(curr->key));
        curr = curr->next;
      }
    }
  }
  printf("\n");
}

void destroy(htable *ht) {
  if (ht == NULL) {
    return;
  }

  for (size_t i = 0; i < ht->capacity; i++) {
    if (ht->buckets[i]) {
      h_entry *tmp = NULL;
      h_entry *curr = ht->buckets[i];

      while (curr) {
        tmp = curr;
        curr = curr->next;
        free((void *)tmp->key);
        free(tmp);
      }
    }
  }

  free(ht->buckets);
  free(ht);
}
