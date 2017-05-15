#include <stdio.h>
#include "bst.h"
#include <stdlib.h>

void printi(V i) {
    printf("%d\n", i);
}

void printn(int k, V v) {
    printf("(%d,%d)\n", k, v);
}

// prints the key of a bst or null if it doesn't exist
char* demangle(struct BST* bst) {
    char** result = malloc(sizeof(*result));
    *result = "*";
    if (bst)
        asprintf(result, "%d", bst->key);
    return *result;
}

void print_bst(struct BST* bst) {
    printf("[%s](%d, %d)[%s, %s]\n",
           demangle(bst->parent),
           bst->key,
           bst->value,
           demangle(bst->left),
           demangle(bst->right));
}

int main(int argc, char** argv) {
    struct BST* bst1 = create_bst(3, 3);
    bst_insert(bst1, 1, 1);
    bst_insert(bst1, 0, 0);
    bst_insert(bst1, 2, 2);
    bst_insert(bst1, 5, 5);
    bst_insert(bst1, 4, 4);
    bst_insert(bst1, 6, 6);
    bst_traverse_bst(bst1, *print_bst);
    printf("\n");

    struct BST* bst2 = create_bst(7,7);
    bst_insert(bst2, 3, 3);
    bst_insert(bst2, 10, 10);
    bst_insert(bst2, 1, 1);
    bst_insert(bst2, 5, 5);
    bst_insert(bst2, 0, 0);
    bst_insert(bst2, 2, 2);
    bst_insert(bst2, 6, 6);
    bst_insert(bst2, 9, 9);
    bst_insert(bst2, 8, 8);
    bst_traverse_bst(bst2, *print_bst);
    printf("\n");

    // delete leaf
    bst_delete(bst2, 0);
    //
    bst_delete(bst2, 8);
    bst_traverse_bst(bst2, *print_bst);
}
