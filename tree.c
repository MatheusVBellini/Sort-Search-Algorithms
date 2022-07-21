#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void create_tree(Tree *tree) {
	tree = (Tree *)malloc(sizeof(Tree));
	tree -> root = NULL;
}

void recursive_delete_tree(Node *node) {
	if (node == NULL)
		return;
	recursive_delete_tree(node -> left);
	recursive_delete_tree(node -> right);
	free(node);
}

void delete_tree(Tree *tree) {
	recursive_delete_tree(tree -> root);
	tree -> root = NULL;
}

int recursive_tree_insert(Node **node, int value) {
	if (*node == NULL) {
		*node = malloc(sizeof(Node));
		(*node) -> value = value;
		(*node) -> left = NULL;
		(*node) -> right = NULL;
		return 0;
	}

	if ((*node) -> value == value)
		return 1;

	return (value < (*node) -> value) ? 
		recursive_tree_insert((*node) -> left, value) : 
		recursive_tree_insert((*node) -> right, value);
}

int insert_tree(Tree *tree, int value) {
	return recursive_tree_insert(&(tree -> root), value);
}

void recursive_print_tree(Node *node, int level) {
	if (node == NULL) 
		return; 
	recursive_print_tree(node -> left, level + 1);
	printf(" level:%d--%d:value ", level, node -> value);
	recursive_print_tree(node -> right, level + 1);
}

void print_tree(Tree tree) {
	recursive_print_tree(tree.root, 0);	
}
