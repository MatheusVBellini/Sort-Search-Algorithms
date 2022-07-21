#ifndef SEARCH_H
#define SEARCH_H

#include "list.h"
#include "tree.h"

int sequential_search(list l, int x);
int sentinel_sequential_search(list l, int x);
int sorted_sequential_search(list l, int x);
int indexed_search(list l, int x) {
int recursive_bin_search(list l, int x, int init, int end);
int binary_search(list l, int x);
int iter_binary_search(list l, int x);
int iter_interpolated_search(list l, int x);
Node recursive_searchtree(Node *node, int value);
Node searchtree(Tree tree, int value);

typedef struct {
	int size;
	int *data;
} c_hash;

int ch_index(int value, int size);
void new_c_hash(c_hash *hash, int size);
int ch_insert(c_hash hash, int value);
int ch_search(c_hash hash, int value);
int ch_delete(c_hash hash, int value);

#endif
