#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include<stdio.h>

Dictionary create() {
	Dictionary dict = malloc(sizeof(Word));
	dict->word = NULL;
	dict->count = 0;
	dict->next = NULL;
	return dict;
}

void add(Dictionary dict, char *str) {
	Dictionary temp = dict;
	
	while (temp->next != NULL) {
		if (strcmp(temp->next->word, str) > 0) {
			Dictionary node = malloc(sizeof(Word));
			node->word = _strdup(str);
			node->count = 1;
			node->next = temp->next;
			temp->next = node;
			return;
		}
		else if (strcmp(temp->next->word, str) == 0) {
			temp->next->count++;
			return;
		}
		temp = temp->next;
	}
	
	temp->next = malloc(sizeof(Word));
	temp->next->word = _strdup(str);
	temp->next->count = 1;
	temp->next->next = NULL;
}

void print(Dictionary dict) {
	Dictionary temp = dict;
	temp = temp->next;
	while (temp != NULL) {
		printf("%d ", temp->count);
		printf("%s", temp->word);
		printf("\n");
		temp = temp->next;
	}
}

void destroy(Dictionary dict) {
	Dictionary temp = dict;
	while (temp != NULL) {
		free(temp->word);
		Dictionary del = temp;
		temp = temp->next;
		free(del);
	}
}

Dictionary filterDictionary(Dictionary indict, int(*filter)(Word *w)) {
	Dictionary prethodni = indict;
	Dictionary trenutni = indict->next;

	while (trenutni != NULL) {
		if (filter(trenutni) == 1) {
			prethodni = prethodni->next;
			trenutni = trenutni->next;
		}
		else {
			prethodni->next = trenutni->next;
			free(trenutni->word);
			free(trenutni);
			trenutni = prethodni->next;
		}
	}

	return indict;
}

int filter(Word *w) {
	if (w->count >= 5 && w->count <= 10 && strlen(w->word) > 3)
		return 1;
	else
		return 0;
}