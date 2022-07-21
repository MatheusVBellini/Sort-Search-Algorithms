#include "sort.h"
#include <stdio.h>

int main() {
	list *l = create_list();
	list *l2 = create_list();

	rand_list(l);
	print_list(*l);
	simple_quicksort(*l);
	print_list(*l);

	printf("\n");


	return 0;
}
