#ifndef LIST_H
#define LIST_H

#define TAM 7
#define RAND_CAP 31

typedef struct {
	int *data;
	int *copy;
	int size;
} list;

list* create_list();
void undo(list *l);
void add_to_list(list *l, int num);
void rand_list(list *l);
void print_list(list l);

#endif 
