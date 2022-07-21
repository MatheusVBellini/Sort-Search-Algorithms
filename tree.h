#ifndef LIST_H
#define LIST_H

typedef struct node {
	int value;
	struct node *left;
	struct node *right;
} Node;

typedef struct {
	Node *root;
} Tree;

void create_tree(Tree *tree);
void recursive_delete_tree(Node *node);
void delete_tree(Tree *tree);
int recursive_tree_insert(Node *node, int value);
int insert_tree(Tree *tree, int value);
void recursive_print_tree(Node *node, int level);
void print_tree(Tree tree);

#endif
