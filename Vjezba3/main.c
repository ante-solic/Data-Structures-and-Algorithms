#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	float x, y, z;
}Vrh;

typedef struct {
	Vrh normala;
	Vrh vrhovi[3];
	unsigned short boja;
}Trokut;

typedef struct {
	Trokut* niz;
	unsigned int n;
}Objekt3D;

Objekt3D* read_file(FILE* f) {
	Objekt3D* o = (Objekt3D*)malloc(sizeof(Objekt3D));

	f = fopen("primjerbin.stl", "rb");
	fseek(f, 80, SEEK_SET);

	fread(&(o->n), sizeof(unsigned int), 1, f);

	o->niz = (Trokut*)malloc(sizeof(Trokut) * (o->n));

	int i = 0;

	while (!feof(f)) {
		fread(&(o->niz[i]), 50, 1, f);
		i++;
	}

	fclose(f);
	return o;
}

void write_file(FILE* f, Objekt3D* o) {
	f = fopen("bin.stl", "wb");
	int zaglavlje[20] = { 0 };

	fwrite(zaglavlje, sizeof(zaglavlje[0]), 20, f);
	fwrite(&(o->n), sizeof(o->n), 1, f);
	for (int i = 0; i < o->n; i++) {
		fwrite(&(o->niz[i]), 50, 1, f);
	}
	fclose(f);
}

void write_text(FILE* f, Objekt3D* o) {
	f = fopen("text.stl", "wt");

	char zaglavlje[] = "solid OpenSCAD_Model\n";
	char string1[] = "  facet normal";
	char string2[] = "    outer loop";
	char string3[] = "        vertex";
	char string4[] = "    endloop";
	char string5[] = "  endfacet";
	char string6[] = "endsolid OpenSCAD_Model";

	fwrite(zaglavlje, sizeof(zaglavlje), 1, f);

	for (int i = 0; i < o->n; i++) {
		fprintf(f, "%s %f %f %f\n", string1, o->niz[i].normala.x, o->niz[i].normala.y, o->niz[i].normala.z);
		fprintf(f, "%s\n", string2);
		fprintf(f, "%s %f %f %f\n", string3, o->niz[i].vrhovi[0].x, o->niz[i].vrhovi[0].y, o->niz[i].vrhovi[0].z);
		fprintf(f, "%s %f %f %f\n", string3, o->niz[i].vrhovi[1].x, o->niz[i].vrhovi[1].y, o->niz[i].vrhovi[1].z);
		fprintf(f, "%s %f %f %f\n", string3, o->niz[i].vrhovi[2].x, o->niz[i].vrhovi[2].y, o->niz[i].vrhovi[2].z);
		fprintf(f, "%s\n", string4);
		fprintf(f, "%s\n", string5);
	}

	fwrite(string6, sizeof(string6), 1, f);

	fclose(f);
}

void delete_objekt(Objekt3D* o) {
	free(o->niz);
	free(o);
}

int main() {
	FILE* f = NULL;
	Objekt3D* o = read_file(f);
	FILE* f1 = NULL;
	write_file(f1, o);
	FILE* f2 = NULL;
	write_text(f2, o);
	delete_objekt(o);

	return 0;
}