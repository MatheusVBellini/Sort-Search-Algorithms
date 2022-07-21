#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

list* create_list() {
	list *l = malloc(sizeof(list));
	l -> data = malloc(TAM * sizeof(int));
	l -> copy = malloc(TAM * sizeof(int));
	l -> size = 0;
	return l;
}

void undo(list *l) {
	free(l -> data);
	l -> size = 0;
}

void add_to_list(list* l, int num) {
	l -> data[l -> size] = num;
	l -> size++;
}

void rand_list(list *l) {
	srand(time(0));
	for (int i = 0; i < TAM; i++) {
		add_to_list(l, rand() % RAND_CAP);
	}
}

void print_list(list l) {
	printf("{");
	for(int i = 0; i < l.size; i++) {
		printf("%d, ", l.data[i]);
	}
	printf("\b\b}\n");
}
