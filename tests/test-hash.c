#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "ds/hash.h"
#include "utils.h"

static uint64_t djb2(const char *s) {
    uint64_t hash = 5381;
    char c;

    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

static uint64_t lose_lose(const char *s) {
    uint64_t hash = 0;
    char c;

    while ((c = *s++)) {
        hash += c;
    }

    return hash;
}

int main(void) {
    // lose_lose is used only to show collisions, don't use it

    hashtable h = hash_init(lose_lose, 1000);

    ut_assert(h.buckets != NULL);
    ut_assert(h.capacity == 1000);

    ut_assert(hash_contains(&h, "febits") == false);
    ut_assert(hash_get(&h, "febits") == NULL);

    ut_assert(hash_insert(&h, "febits", NULL) == true);
    ut_assert(hash_contains(&h, "febits") == true);
    ut_assert(hash_get(&h, "febits") != NULL);
    ut_assert(hash_insert(&h, "febits", NULL) == false);

    ut_assert(hash_insert(&h, "feklipe", NULL) == true);
    ut_assert(hash_contains(&h, "feklipe") == true);
    ut_assert(hash_get(&h, "feklipe") != NULL);
    ut_assert(hash_insert(&h, "feklipe", NULL) == false);

    ut_assert(hash_insert(&h, "linux", NULL) == true);
    ut_assert(hash_contains(&h, "linux") == true);
    ut_assert(hash_get(&h, "linux") != NULL);
    ut_assert(hash_insert(&h, "linux", NULL) == false);

    ut_assert(hash_insert(&h, "dog", NULL) == true);
    ut_assert(hash_contains(&h, "dog") == true);
    ut_assert(hash_get(&h, "dog") != NULL);
    ut_assert(hash_insert(&h, "dog", NULL) == false);

    ut_assert(hash_insert(&h, "god", NULL) == true);
    ut_assert(hash_contains(&h, "god") == true);
    ut_assert(hash_get(&h, "god") != NULL);
    ut_assert(hash_insert(&h, "god", NULL) == false);

    ut_assert(hash_insert(&h, "ogd", NULL) == true);
    ut_assert(hash_contains(&h, "ogd") == true);
    ut_assert(hash_get(&h, "ogd") != NULL);
    ut_assert(hash_insert(&h, "ogd", NULL) == false);

    ut_assert(hash_delete(&h, "pow") == false);

    ut_assert(hash_delete(&h, "febits") == true);
    ut_assert(hash_contains(&h, "febits") == false);

    ut_assert(hash_delete(&h, "god") == true);
    ut_assert(hash_contains(&h, "god") == false);

    ut_assert(hash_delete(&h, "dog") == true);
    ut_assert(hash_contains(&h, "dog") == false);

    ut_assert(hash_delete(&h, "ogd") == true);
    ut_assert(hash_contains(&h, "ogd") == false);

    ut_assert(hash_delete(&h, "feklipe") == true);
    ut_assert(hash_contains(&h, "feklipe") == false);

    ut_assert(hash_delete(&h, "linux") == true);
    ut_assert(hash_contains(&h, "linux") == false);

    hash_destroy(&h);

    return EXIT_SUCCESS;
}
