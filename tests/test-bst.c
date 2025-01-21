#include <stdio.h>
#include <stdlib.h>

#include "ds/bst.h"
#include "types.h"
#include "utils.h"

int main(void) {
    u64 arr[] = {40, 20, 60, 10, 50, 30, 70, 5};

    ut_print_array(arr, ARRSIZE(arr));

    bst_node *root = NULL;

    for (size_t i = 0; i < ARRSIZE(arr); i++) {
        ut_assert(bst_insert(&root, &arr[i], ut_compare_u64) == true);
    }

    ut_assert(UT_GETAS(root->data, u64 *) == 40);
    ut_assert(UT_GETAS(root->left->data, u64 *) == 20);
    ut_assert(UT_GETAS(root->right->data, u64 *) == 60);
    ut_assert(UT_GETAS(root->left->left->data, u64 *) == 10);
    ut_assert(UT_GETAS(root->right->right->data, u64 *) == 70);
    ut_assert(UT_GETAS(root->left->right->data, u64 *) == 30);
    ut_assert(UT_GETAS(root->right->left->data, u64 *) == 50);
    ut_assert(UT_GETAS(root->left->left->left->data, u64 *) == 5);

    ut_assert(bst_search(root, &arr[7], ut_compare_u64) != NULL);
    ut_assert(
        UT_GETAS(bst_search(root, &arr[7], ut_compare_u64)->data, u64 *) == 5);

    ut_assert(bst_size(root) == 8);
    ut_assert(bst_height(root) == 4);

    ut_assert(bst_min(root) != NULL);
    ut_assert(UT_GETAS(bst_min(root)->data, u64 *) == 5);

    ut_assert(bst_max(root) != NULL);
    ut_assert(UT_GETAS(bst_max(root)->data, u64 *) == 70);

    ut_assert(bst_delete(&root, &arr[3], ut_compare_u64) == true);
    ut_assert(UT_GETAS(root->left->left->data, u64 *) == 5);
    ut_assert(bst_size(root) == 7);
    ut_assert(bst_height(root) == 3);

    ut_assert(bst_delete(&root, &arr[6], ut_compare_u64) == true);
    ut_assert(bst_size(root) == 6);
    ut_assert(bst_height(root) == 3);
    ut_assert(bst_max(root) != NULL);
    ut_assert(UT_GETAS(bst_max(root)->data, u64 *) == 60);

    ut_assert(bst_delete(&root, &arr[1], ut_compare_u64) == true);
    ut_assert(bst_size(root) == 5);
    ut_assert(bst_height(root) == 3);
    ut_assert(UT_GETAS(root->left->data, u64 *) == 30);

    ut_assert(bst_delete(&root, &arr[0], ut_compare_u64) == true);
    ut_assert(bst_size(root) == 4);
    ut_assert(bst_height(root) == 3);
    ut_assert(UT_GETAS(root->data, u64 *) == 50);

    ut_assert(bst_delete(&root, &arr[7], ut_compare_u64) == true);
    ut_assert(bst_size(root) == 3);
    ut_assert(bst_height(root) == 2);

    ut_assert(bst_delete(&root, &arr[2], ut_compare_u64) == true);
    ut_assert(bst_size(root) == 2);
    ut_assert(bst_height(root) == 2);

    ut_assert(bst_delete(&root, &arr[4], ut_compare_u64) == true);
    ut_assert(bst_size(root) == 1);
    ut_assert(bst_height(root) == 1);
    ut_assert(UT_GETAS(root->data, u64 *) == 30);

    ut_assert(bst_delete(&root, &arr[5], ut_compare_u64) == true);
    ut_assert(bst_size(root) == 0);
    ut_assert(bst_height(root) == 0);
    ut_assert(root == NULL);

    bst_destroy(&root);
    ut_assert(root == NULL);

    return EXIT_SUCCESS;
}
