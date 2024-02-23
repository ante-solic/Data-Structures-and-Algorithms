#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

HashTable *NewTable(int size)
{
	// kreira novu hash tablicu (alocira samu strukturu i niz pokazivaèa)
	HashTable *h = malloc(sizeof(HashTable));
	h->table = malloc(size * sizeof(Bin));
	h->size = size;
	h->load = 0;

	for (int i = 0; i < size; i++)
		h->table[i] = NULL;

	return h;
}

unsigned int hash(char *word)
{
	// od kljuca generira hash kod
	unsigned int key = 0;
	while(*word != '\0')
	{
		key = key*HCONST + *word;
		word++;
	}
	return key;
}

void Insert(HashTable *ht, char *word)
{
	// dodaje novu rijec u listu na odgovarajucem pretincu
	Bin* node = malloc(sizeof(Bin));

	int i = hash(word) % ht->size;

	node->word = word;
	node->next = ht->table[i];

	ht->table[i] = node;
	ht->load++;
}

int Get(HashTable *ht, char *word)
{
	// vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici

	int i = hash(word) % ht->size;

	Bin* temp = ht->table[i];

	while (temp != NULL) {
		if (!strcmp(temp->word, word))
			return 1;
		temp = temp->next;
	}

	return 0;
}

void DeleteTable(HashTable *ht)
{
	// brise cijelu hash tablicu (liste na svim pretincima (rijec i element liste), pretince ...)

	for (int i = 0; i < ht->size; i++) {
		Bin* node = ht->table[i];

		while (node != NULL) {
			Bin* del = node;
			node = node->next;
			free(del->word);
			free(del);
		}
	}

	free(ht->table);
	free(ht);
}