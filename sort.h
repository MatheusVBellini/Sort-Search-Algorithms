#ifndef SORT_H
#define SORT_H

#include "list.h"
#include "tree.h"

void recursive_merge(list l, int start, int end);
void merge_sort(list l);
void simple_selection(list l);
void bubble_sort(list l);
void rec_simple_quicksort(list l, int init, int end);
void simple_quicksort(list l);
void rec_quicksort(list l, int init, int end);
void quick_sort(list l);
void insertion_sort(list l);
void shell_sort(list l);
void arrange_max_heap(list l, int i, int heap_size);
void build_max_heap(list l);
void heap_sort(list l);
void iter_build_max_heap(list l, int size);
void iter_heapsort(list l);
void minimumcountingsort(list l);
void counting_sort(list l);
int get_number_of_digits(int value);
int get_digit(int value, int index);
void radix_sort(list l);

#endif
