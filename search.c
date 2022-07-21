#include "search.h"

// sequential search
// O(n)

// simple
int sequential_search(list l, int x) {
	for (int i = 0; i < l.size; i++)
		if (l.data[i] == x)
			return i;
	return -1;
}

// with sentinel
int sentinel_sequential_search(list l, int x) {
	int i;
	l.data[l.size] = x;
	for (i = 0; l.data[i] != x; i++);
	return (i < l.size) ? i : -1;
}

// in sorted list
int sorted_sequential_search(list l, int x) {
	for (int i = 0; l.data[i] <= x; i++)
		if (l.data[i] == x)
			return i;
	return -1;
}

// indexed

int indexed_search(list l, int x) {
	int i, j;
	int index_table_size = l.size / 5;
	int *t = (int *)malloc(index_table_size * sizeof(int));
	for (i = 0; i < index_table_size; i++)
		t[i] = i * l.size / index_table_size;

	for (i = 0; i < index_table_size && l.data[t[i]] < x; i++);

	if (i == 0)
		return (x == l.data[t[i]]) ? i : -1;

	for (j = t[i-1]; j < l.size && l.data[j] <= x; j++)
		if (l.data[j] == x)
			return j;
	return -1;
}

//****************************


// binary search
// O(log n)

int recursive_bin_search(list l, int x, int init, int end) {
	int mid = (init + end) / 2;
	if (init >= end) {
		if (l.data[init] == x)
			return init;
		return -1;
	} 
	if (l.data[mid] == x)
		return mid;
	
	return (l.data[mid] > x) ? recursive_bin_search(l, x, init, mid-1) : recursive_bin_search(l, x, mid+1, end); 
}

int rec_binary_search(list l, int x) {
	return recursive_bin_search(l, x, 0, l.size-1);
}

int iter_binary_search(list l, int x) {
	int init = 0, end = l.size - 1;
	int mid;

	while (init <= end) {
		mid = (init + end) / 2;
		if (l.data[mid] == x)
			return mid;
		if (x < l.data[mid])
			end = mid - 1;
		else
			init = mid + 1;
	}

	return -1;
}

int iter_interpolated_search(list l, int x) {
	int init = 0, end = l.size - 1;
	int mid;

	while (init <= end) {
		mid = init + (end - init) * ((x - l.data[init]) / (l.data[end] - l.data[init]));
		if (l.data[mid] == x)
			return mid;
		if (x < l.data[mid])
			end = mid - 1;
		else
			init = mid + 1;
	}

	return -1;
}

//****************************


// search-tree
// O(log n)

Node recursive_searchtree(Node *node, int value) {
	if (node == NULL || node -> value == x)
		return node;
	return (value < node -> value) ? 
		recursive_searchtree(node -> left, value) : 
		recursive_searchtree(node -> right, value);
}

Node searchtree(Tree tree, int value) {
	return recursive_searchtree(tree -> root, value);
}

//****************************


// Static Hash
// O(c)

// closed hash
int ch_index(int value, int size) {
	return value % size;
}

void new_c_hash(c_hash *hash, int size) {
	hash -> size = size;
	hash -> data = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		hash -> data[i] = -1;
}

int ch_insert(c_hash hash, int value) {
	int i = ch_index(value, hash.size);
	int og_i = i;

	if (hash.data[i] == value)
		return -1; /* value already in place */
	
	if (hash.data[i] == -1 || hash.data[i] == -2) {
		hash.data[i] = value;
		return 0; /* value succesfully inserted */
	} 
	else {
		while (hash.data[i] == -1 || hash.data[i] == -2) {
			i = (i + 1) % (hash.size);
			if (i == og_i)
				return -2; /* no empty space for variable */
		}
		hash.data[i] = value;
		return 0; /* value succesfully inserted */
	}

	return -3; /* fatal error */
}

int ch_search(c_hash hash, int value) {
	int i = ch_index(value, hash.size);
	int og_i = i;

	while (hash.data[i] != value) {
		i = (i + 1) % (hash.size);
		if (i == og_i)
			return -1; /* value not found */
	}
	return i; /* value found */
}

int ch_delete(c_hash hash, int value) {
	int i = ch_search(hash, value);
	if (i == -1)
		return -1; /* value not found */
	hash.data[i] = -2;
	return 0; /* value deleted */
}


// open hash


//*************************************************
