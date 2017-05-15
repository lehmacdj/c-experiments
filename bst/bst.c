#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

void printbst(struct BST* bst) {
    printf("[%p](%d, %d)[%p, %p] at %p\n",
           bst->parent,
           bst->key,
           bst->value,
           bst->left,
           bst->right,
           bst);
}

struct BST* create_bst(int k, V v) {
    struct BST* bst = malloc(2 * sizeof(int) + 3 * sizeof(void*));
    if (bst == NULL) {
        printf("Wasn't able to allocate memory!");
        return NULL;
    }

    bst->key = k;
    bst->value = v;
    bst->left = NULL;
    bst->right = NULL;
    bst->parent = NULL;
    return bst;
}

void destroy_bst(struct BST* bst) {
    printf("destroy bst: %p\n", bst);
    if (bst == NULL)
        return;

    destroy_bst(bst->left);
    destroy_bst(bst->right);
    free(bst);
    bst = NULL;
}

/**
 * Returns the subtree of [bst] closest to [k].
 */
struct BST* tree_containing_key(struct BST* bst, int k) {
    struct BST* b = bst;

    while ((k < b->key && b->left) || (k > b->key && b->right)) {
        if (k < b->key) {
            b = b->left;
        } else if (k > b->key) {
            b = b->right;
        }
    }

    return b;
}

V* bst_search(struct BST* bst, int k) {
    struct BST* b = tree_containing_key(bst, k);
    return b->key == k ? &b->value : NULL;
}

void bst_insert(struct BST* bst, int k, V v) {
    struct BST* b = tree_containing_key(bst, k);

    if (k < b->key) {
        b->left = create_bst(k, v);
        b->left->parent = b;
    } else if (k == b->key) {
        b->value = v;
    } else {
        b->right = create_bst(k, v);
        b->right->parent = b;
    }
}

/**
 * Find the minimum key in the tree.
 */
struct BST* find_min(struct BST* bst) {
    struct BST* b = bst;
    while(b) {
        b = b->left;
    }
    return b;
}

/**
 * Replace [bst] with [node]. [node] should be an orphaned node (e.g. has no
 * pointers to it within the tree).
 */
void replace_node_in_parent(struct BST* bst, struct BST* node) {
    struct BST* parent = bst->parent;

    if (parent->left == bst)
        parent->left = node;
    if (parent->right == bst)
        parent->right = node;
    if (node != NULL)
        node->parent = parent;
}

void bst_delete(struct BST* bst, int k) {
    struct BST* b = tree_containing_key(bst, k);

    if (b->key != k)
        return;

    if (b->left && b->right) {
        struct BST* mid = find_min(b->right);
        mid->parent->left = NULL;
        mid->left = b->left;
        mid->right = b->right;
        replace_node_in_parent(b, mid);
    } else if (b->left) {
        replace_node_in_parent(b, b->left);
    } else if (b->right) {
        replace_node_in_parent(b, b->right);
    } else {
        replace_node_in_parent(b, NULL);
    }
}

void bst_traverse_value(struct BST* bst, VConsumer c) {
    if (bst == NULL)
        return;

    bst_traverse_value(bst->left, c);
    (*c)(bst->value);
    bst_traverse_value(bst->right, c);
}

void bst_traverse_node(struct BST* bst, NConsumer c) {
    if (bst == NULL)
        return;

    bst_traverse_node(bst->left, c);
    (*c)(bst->key, bst->value);
    bst_traverse_node(bst->right, c);
}

void bst_traverse_bst(struct BST* bst, BConsumer c) {
    if (bst == NULL)
        return;

    bst_traverse_bst(bst->left, c);
    (*c)(bst);
    bst_traverse_bst(bst->right, c);
}
