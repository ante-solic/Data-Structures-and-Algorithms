#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
	void* data;
	int priority;
}Element;

void swap(Element* arr, int c, int r) {
	int temp = arr[r].priority;
	arr[r].priority = arr[c].priority;
	arr[c].priority = temp;
}

/* Recursive
void toTop(Element *arr,int c) {
	int r = (c - 1) / 2;

	if (arr[r].priority < arr[c].priority) {
		swap(arr, c, r);
		toTop(arr, r);
	}
}
*/

// Iterative
void toTop(Element* arr, int c) {
	int r = (c - 1) / 2;

	while (arr[r].priority < arr[c].priority) {
		swap(arr, c, r);
		c = r;
		r = (c - 1) / 2;
	}
}

/* Recursive
void toBottom(Element* arr, int r, int *i) {
	int l = 2 * r + 1;
	int d = 2 * r + 2;

	if (l >= *i && d >= *i)
		return;
	else if (r >= *i && l < *i) {
		if (arr[r].priority < arr[l].priority) {
			swap(arr, r, l);
		}
	}
	else if (arr[r].priority < arr[l].priority && arr[r].priority < arr[d].priority) {
		if (arr[l].priority > arr[d].priority) {
			swap(arr, l, r);
			toBottom(arr, l, i);
		}
		else {
			swap(arr, d, r);
			toBottom(arr, d, i);
		}
	}
}*/


// Iterative
void toBottom(Element* arr, int r, int *i) {
	int l = 2 * r + 1;
	int d = 2 * r + 2;

	while (arr[r].priority < arr[l].priority || arr[r].priority < arr[d].priority) {

		if (l >= *i && d >= *i)
			return;
		else if (r >= *i && l < *i) {
			if (arr[r].priority < arr[l].priority) {
				swap(arr, r, l);
				return;
			}
		}
		else if (arr[l].priority > arr[d].priority) {
			swap(arr, l, r);
			l = r;
			l = 2 * r + 1;
			d = 2 * r + 2;
		}
		else {
			swap(arr, d, r);
			d = r;
			d = 2 * r + 2;
			l = 2 * r + 1;
		}
	}
}

void add(Element *arr,int n,int *i) {
	arr[*i].priority = n;
	toTop(arr, *i);
	(*i)++;
}

void delete(Element* arr, int* i) {
	arr[0].priority = arr[(*i) - 1].priority;
	arr[(*i) - 1].priority = 0;
	toBottom(arr, 0, i);
	(*i)--;
}

void print(Element* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i].priority);
	}
	printf("\n");
}

int main() {
	Element arr[10000];
	int i = 0;

	while (i < 50) {
		arr[i].priority = 100;
		i++;
	}

	i = 0;

	add(arr, 10, &i);
	add(arr, 15, &i);
	add(arr, 4, &i);
	add(arr, 13, &i);
	add(arr, 14, &i);
	add(arr, 1, &i);
	add(arr, 45, &i);
	print(arr, i);

	delete(arr, &i);

	print(arr, i);
}