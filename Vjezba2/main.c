#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	float x;
	float y;
} Tocka;

typedef struct {
	Tocka* niz;
	int n;
} Poligon;

int* podniz(int* niz, int start, int stop) {
	int* temp;
	temp = (int*)malloc((stop - start) * sizeof(int));
	int n = 0;
	for (int i = start; i < stop; i++) {
		temp[n] = niz[i];
		n++;
	}

	return temp;
}

int* filtriraj(int* niz, int n, int th, int* nth) {
	int* temp;
	temp = (int*)malloc(n * sizeof(int));
	int j = 0;

	for (int i = 0; i < n; i++) {
		if (niz[i] < th) {
			temp[j] = niz[i];
			j++;
		}
	}

	*nth = j;

	return temp;
}

int** podijeli(int* niz, int n) {

	int* temp1;
	int* temp2;
	int x = n / 2;
	int y = n - x;
	temp1 = (int*)malloc((x) * sizeof(int));
	temp2 = (int*)malloc((y) * sizeof(int));

	int a = 0, b = 0;

	for (int i = 0; i < x; i++) {
		temp1[a] = niz[i];
		a++;
	}

	for (int i = x; i < n; i++) {
		temp2[b] = niz[i];
		b++;
	}

	int** temp3 = (int**)malloc(2 * sizeof(int*));
	temp3[0] = temp1;
	temp3[1] = temp2;

	return temp3;
}

Poligon* novi_poligon(float* niz_x, float* niz_y, int n) {
	if (n >= 3) {
		Poligon* p = (Poligon*)malloc(sizeof(Poligon));
		p->niz = (Tocka*)malloc(sizeof(Tocka) * n);

		for (int i = 0; i < n; i++) {
			p->niz[i].x = niz_x[i];
			p->niz[i].y = niz_y[i];
		}

		return p;
	}
	else {
		printf("Broj unesenih tocaka mora biti veci od 2!");
		return 0;
	}
}

Tocka** pozitivni(Poligon* p, int* np) {
	int counter = 0;
	int j = 0;
	for (int i = 0; i < p->n; i++) {
		if (p->niz[i].x > 0 && p->niz[i].y > 0)
		{
			counter++;
		}
	}
	Tocka** temp = (Tocka**)malloc(sizeof(Tocka*) * counter);

	for (int i = 0; i < p->n; i++) {
		if (p->niz[i].x > 0 && p->niz[i].y > 0)
		{
			temp[j] = &p->niz[i];
			j++;
		}
	}
	*np = j;
	return temp;
}

int main() {
	int niz[] = { 3,12,1,15,8,4,2 };

	int* niz2 = podniz(niz, 2, 5);

	for (int i = 0; i < 3; i++) {
		printf("%d ", niz2[i]);
	}
	printf("\n");

	int nth = 0;
	int* niz3 = filtriraj(niz, sizeof(niz) / sizeof(niz[0]), 5, &nth);

	for (int i = 0; i < nth; i++) {
		printf("%d ", niz3[i]);
	}
	printf("\n");

	int** niz4 = podijeli(niz, sizeof(niz) / sizeof(niz[0]));

	for (int i = 0; i < 2; i++) {
		if (i == 1) {
			for (int j = 0; j < sizeof(niz) / sizeof(niz[0]) - ((sizeof(niz) / sizeof(niz[0])) / 2); j++) {
				printf("%d ", niz4[i][j]);
			}
		}
		else {
			for (int j = 0; j < ((sizeof(niz) / sizeof(niz[0])) / 2); j++) {
				printf("%d ", niz4[i][j]);
			}
		}
		printf("\n");
	}

	int n;
	printf("Unesi broj tocaka: ");
	scanf("%d", &n);
	float* niz_x = (float*)malloc(n * sizeof(float));
	float* niz_y = (float*)malloc(n * sizeof(float));

	for (int i = 0; i < n; i++) {
		printf("Unesi tocku x%d: ", i + 1);
		scanf("%f", &niz_x[i]);
		printf("Unesi tocku y%d: ", i + 1);
		scanf("%f", &niz_y[i]);
	}

	Poligon* p = novi_poligon(niz_x, niz_y, n);
	printf("Tocke poligona su: \n");
	for (int i = 0; i < n; i++) {
		printf("%f %f \n", p->niz[i].x, p->niz[i].y);
	}
	p->n = n;
	Tocka** t = pozitivni(p, &n);
	printf("Pozitivne tocke su: \n");
	for (int i = 0; i < n; i++) {
		printf("%f %f\n", t[i]->x, t[i]->y);
	}

	return 0;
}