#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BIGRAND (rand()*rand())

void shuffle(int* niz, int n) {
	for (int i = 0; i < n - 1; i++) {
		int j = i + BIGRAND % (n - i);
		int tmp = niz[i];
		niz[i] = niz[j];
		niz[j] = tmp;
	}
}

int* generate(int n) {
	int* niz = (int*)malloc(sizeof(int) * n);
	niz[0] = 1 + BIGRAND % 3;
	for (int i = 1; i < n; i++)
		niz[i] = niz[i - 1] + BIGRAND % 3 + 1;
	shuffle(niz, n);
	return niz;
}


void presjek(int *niz, int *niz2, int n) {
	int counter = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (niz[i] == niz2[j])
				counter++;
		}
	}

	printf("Duljina presjeka -> %d ", counter);
}

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void presjek_jedan_sortiran(int* niz, int* niz2,int n) {
	int counter = 0;

	qsort(niz2, n, sizeof(int), compare);

	printf("\n");
	for (int i = 0; i < n; i++) {
		if (bsearch(&niz[i], niz2, n, sizeof(int), compare) != NULL)
			counter++;
	}

	printf("Duljina presjeka -> %d", counter);
}

void presjek_oba_sortirana(int* niz, int* niz2, int n,int n1) {
	int counter = 0;
	int i = 0, j = 0;
	qsort(niz, n, sizeof(int), compare);
	qsort(niz2, n, sizeof(int), compare);

	while (i < n && j < n1) {
		if (niz[i] == niz2[j]) {
			counter++;
			i++;
			j++;
		}
		else if (niz[i] < niz2[j]) {
			i++;
		}
		else
			j++;
	}

	printf("Duljina presjeka -> %d ", counter);
}

void presjek_po_indeksima(int* niz, int* niz2, int n) {
	int* indexA;
	int* indexB;
	int* presjek;

	int maxA = niz[0];
	int maxB = niz2[0];
	int max;
	int min;

	for (int i = 0; i < n; i++) {
		if (niz[i] > maxA)
			maxA = niz[i];
		if (niz2[i] > maxB)
			maxB = niz2[i];
	}

	if (maxA >= maxB) {
		max = maxA;
		min = maxB;
	}
	else {
		max = maxB;
		min = maxA;
	}

	indexA = (int*)malloc(sizeof(int) * (maxA+1));
	indexB = (int*)malloc(sizeof(int) * (maxB+1));


	for (int i = 0; i < maxA+1; i++) {
		indexA[i] = 0;
	}

	for (int i = 0; i < maxB+1; i++) {
		indexB[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		indexA[niz[i]] = 1;
		indexB[niz2[i]] = 1;
	}
	
	int counter = 0;
	for (int i = 0; i < min; i++) {
		if (indexA[i] == indexB[i] && indexA[i] == 1) {
			counter++;
		}
	}
	presjek = (int*)malloc(sizeof(int) * (counter));

	int j = 0;
	for (int i = 0; i < min; i++) {
		if (indexA[i] == indexB[i] && indexA[i] == 1) {
			presjek[j] = i;
			j++;
		}
	}
	
	free(indexA);
	free(indexB);
	free(presjek);
}

void main() {

	srand(time(NULL));

	clock_t start, end;

	int* niz;

	int* niz2;
	
	for (int i = 10000; i < 100000; i += 10000) {
		niz = generate(i);
		niz2 = generate(i);

		start = clock();
		presjek(niz, niz2, i);
		end = clock();

		printf("\n%f\n", (double)(end - start) / CLOCKS_PER_SEC);

		free(niz);
		free(niz2);
	}
	
	/*
	for (int i = 100000; i < 3000000; i += 300000) {
		niz = generate(i);
		niz2 = generate(i);

		start = clock();
		presjek_jedan_sortiran(niz, niz2, i);
		end = clock();

		printf("\n%f\n", (double)(end - start) / CLOCKS_PER_SEC);

		free(niz);
		free(niz2);
	}
	*/
	/*
	for (int i = 100000; i < 3000000; i += 300000) {
		niz = generate(i);
		niz2 = generate(i);

		start = clock();
		presjek_oba_sortirana(niz, niz2, i, i);
		end = clock();

		printf("\n%f\n", (double)(end - start) / CLOCKS_PER_SEC);

		free(niz);
		free(niz2);
	}
	*/
	/*
	for (int i = 100000; i < 3000000; i += 300000) {
		niz = generate(i);
		niz2 = generate(i);

		start = clock();
		presjek_po_indeksima(niz, niz2, i);
		end = clock();

		printf("\n%f\n", (double)(end - start) / CLOCKS_PER_SEC);

		free(niz);
		free(niz2);
	}
	*/
}