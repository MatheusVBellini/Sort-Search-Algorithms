#include <stdlib.h>
#include "sort.h"
#include "tree.h"

// merge-sort 
// O(nlogn)

void recursive_merge(list l, int start, int end) {
	if (start == end)
		return;
	
	// vector partitioning
	int middle = (start + end) / 2;
	recursive_merge(l, start, middle);
	recursive_merge(l, middle+1, end);


	// apply mergesort
	int i = start, k = start, j = middle+1;
	while (i <= middle && j <= end) {
		if (l.data[i] <= l.data[j]) {
			l.copy[k] = l.data[i];
			k++; i++;
		} else {
			l.copy[k] = l.data[j];
			k++; j++;
		}
	}

	for (; i <= middle; i++) {
		l.copy[k] = l.data[i];
		k++; i++;
	}
	for (; j <= end; j++) {	
		l.copy[k] = l.data[j];
		k++; j++;
	}

	// copy values to data
	for (i = start; i <= end; i++) {
		l.data[i] = l.copy[i];
	}
}

void merge_sort(list l) {
	recursive_merge(l, 0, l.size-1);
}

//*************************************************


// simple selection 
// O(n^2)

void simple_selection(list l) {
	int min, id, tmp;
	for (int i = 0; i < l.size - 1; i++) {
		min = l.data[i];
		id = i;
		for (int j = i+1; j < l.size; j++) {
			if (l.data[j] < min) {
				min = l.data[j];
				id = j;
			}
		}

		tmp = l.data[i];
		l.data[i] = l.data[id];
		l.data[id] = tmp;
	}
}

//*************************************************


// bubble-sort 
// O(n^2)

void bubble_sort(list l) {
	int tmp, swap;
	for (int i = 1; swap != 0 && i < l.size; i++) {
		swap = 0;
		for (int j = 0; j < l.size - i; j++)
			if (l.data[j] > l.data[j+1]) {
				tmp = l.data[j];
				l.data[j] = l.data[j+1];
				l.data[j+1] = tmp;
				swap = 1;
			}	
	}
}

//*************************************************


// quick-sort (simple partioning) 
// regular-case: O(nlogn) 
// worst-case: O(n^2)

void rec_simple_quicksort(list l, int init, int end) {
	if (init >= end)
		return;
	int middle = (init + end) / 2, tmp;
	int pivot = l.data[middle];

	int i = init, j = end;
	while(1) {
		for (; l.data[i] < pivot; i++);
		for (; l.data[j] > pivot; j--);
		
		if (i==j)
			break;

		tmp = l.data[j];
		l.data[j] = l.data[i];
		l.data[i] = tmp;
	}

	rec_simple_quicksort(l, init, i - 1);
	rec_simple_quicksort(l, i + 1, end);
}

void simple_quicksort(list l) {
	rec_simple_quicksort(l, 0, l.size-1);	
}

//*************************************************


// quick-sort (partition for duplicates) 
// regular-case: O(nlogn) 
// worst-case: O(n^2)

void rec_quicksort(list l, int init, int end) {
	if (init >= end) 
		return;

	int middle = (init + end) / 2;
	int pivot = l.data[middle];
	int i = init, j = init, tmp;

	l.data[middle] = l.data[end];
	l.data[end] = pivot;

	while (j < end) {
		if (l.data[j] <= pivot) {
			tmp = l.data[i];
			l.data[i] = l.data[j];
			l.data[j] = tmp;
			i++;
		}
		j++;
	}

	tmp = l.data[i];
	l.data[i] = l.data[j];
	l.data[j] = tmp;

	rec_quicksort(l, init, i-1);
	rec_quicksort(l, i+1, end);
}

void quick_sort(list l) {
	rec_quicksort(l, 0, l.size-1);
}

//*************************************************


// insertion-sort
// O(n^2)

void insertion_sort(list l) {
	int element, j;

	for (int i = 1; i < l.size; i++) {
		element = l.data[i];
		for (int j = i - 1; element < l.data[j] && j >= 0; j--)
			l.data[j + 1] = l.data[j];
		j++;
		l.data[j] = element;
	}

}

//*************************************************


// shell-sort
// O(n(logn)^2)

void shell_sort(list l) {
	int *sequence = NULL;
	int last = 0, h, element;
	int i, j;

	sequence = (int *)malloc(sizeof(int));
	sequence[last] = 1;

	while (l.size > sequence[last]) {
		last++;
		sequence = (int *)realloc(sequence, (last + 1) * sizeof(int));
		sequence[last] = 3 * sequence[last - 1] + 1;
	}
	last--;

	for (; last >= 0; last--) {
		h = sequence[last];
		for (int k = 0; k < h; k++) {
			for (i = h + k; i < l.size; i += h) {
				element = l.data[i];
				for (j = i - h; element < l.data[j] && j >= 0; j -= h)
					l.data[h + j] = l.data[j];
				l.data[h + j] = element;
			}
		}
	}

	free(sequence);

}

//*************************************************


// heap-sort
// O(nlogn)

void arrange_max_heap(list l, int i, int heap_size) {
	int left_node, right_node, biggest_node;
	int tmp;

	left_node = (2 * i + 1 < heap_size) ? 2 * i + 1 : -1;
	right_node = (2 * i + 2 < heap_size) ? 2 * i + 2 : -1;

	if (left_node == -1)
		return;

	biggest_node = (right_node == -1 || l.data[left_node] > l.data[right_node]) ? left_node : right_node;

	if (l.data[i] >= l.data[biggest_node])
		return;

	tmp = l.data[i];
	l.data[i] = l.data[biggest_node];
	l.data[biggest_node] = tmp;

	arrange_max_heap(l, biggest_node, heap_size);

}

void build_max_heap(list l) {
	for (int i = l.size/2 - 1; i >= 0; i--)
		arrange_max_heap(l, i, l.size);
}

void heap_sort(list l) {
	int heap_size, tmp;

	build_max_heap(l);

	heap_size = l.size;
	for (int i = 0; i < l.size - 1; i++) {
		tmp = l.data[0];
		l.data[0] = l.data[heap_size - 1];
		l.data[heap_size - 1] = tmp;

		heap_size--;

		arrange_max_heap(l, 0, heap_size);
	}

}

//*************************************************


// minimum-counting-sort
// O(n^2)

void minimumcountingsort(list l) {
	int *positions = (int *)calloc(l.size, sizeof(int));

	for (int i = 0; i < l.size; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (l.data[i] > l.data[j])
				positions[i]++;
			else
				positions[j]++;
		}
	}

	for (int i = 0; i < l.size; i++)
		l.copy[positions[i]] = l.data[i];
	
	for (int i = 0; i < l.size; i++)
		l.data[i] = l.copy[i];
}

//*************************************************


// counting-sort
// O(n)

void counting_sort(list l) {
	int max, min;

	max = min = l.data[0];
	for (int i = 0; i < l.size; i++) {
		if (l.data[i] > max)
			max = l.data[i];
		if (l.data[i] < min)
			min = l.data[i];
	}

	int *counting = (int *)calloc(max - min + 1, sizeof(int));
	for (int i = 0; i < l.size; i++)
		counting[l.data[i] - min]++;
	
	int j;
	for (int i = 0; i < max - min + 1; i++) {
		j = 0;
		while (j < counting[i])
			l.data[j++] = min + i;
	}

}

//*************************************************


// radix-sort
// O(n)

int get_number_of_digits(int value) {
	int count = 1;
	while (value >= 10) {
		value /= 10;
		count++;
	}
	return count;
}

int get_digit(int value, int index) {
	while (index > 0) {
		value /= 10;
		index--;
	}
	return value % 10;
}

void radix_sort(list l) {
	int queue, n_digits, max;
	int i, j, k;
	int *queues[10];
	int queue_size[10] = {0,0,0,0,0,0,0,0,0,0};

	for (queue = 0; queue < 10; queue++)
		queues[queue] = malloc(l.size * sizeof(int));

	max = l.data[0];
	for (i = 0; i < l.size; i++)
		if (l.data[i] > max)
			max = l.data[i];

	n_digits = get_number_of_digits(max);

	for (j = 0; j < n_digits; j++) {
		for (i = 0; i < l.size; i++) {
			queue = get_digit(l.data[i], j);
			queues[queue][queue_size[queue]++] = l.data[i];
		}

		i = 0;
		for (queue = 0; queue < 10; queue++) {
			for (k = 0; k < queue_size[queue]; k++)
				l.data[i++] = queues[queue][k];

			queue_size[queue] = 0;
		}
	}

	for (queue = 0; queue < 10; queue++)
		free(queues[queue]);
}

//*************************************************
