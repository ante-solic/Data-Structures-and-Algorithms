#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree()
{
	// Novo prazno stablo
	BSTree tree = NULL;
	return tree;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se traži mjesto za novi èvor u stablu. Ako rijeè postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokazivaè.

	if (*bst == NULL) {
		*bst = malloc(sizeof(Node));
		(*bst)->left = NULL;
		(*bst)->right = NULL;
		(*bst)->word = word;
	}
	else if (strcmp((*bst)->word, word) == 0)
		free(word);

	else if (strcmp((*bst)->word, word) > 0)
		AddNode(&(*bst)->left, word);

	else if (strcmp((*bst)->word, word) < 0)
		AddNode(&(*bst)->right, word);
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se pronašla najduža grana (visina stabla).
	
	int maxL = 0;
	int maxR = 0;

	if (bst == NULL)
		return 0;

	maxL = BSTHeight(bst->left);
	
	maxL = BSTHeight(bst->right);
	
	if (maxL > maxR)
		return maxL + 1;
	else
		return maxR + 1;
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rijeèi u stablu na ekran po abecednom redu.
	// In-order šetnja po stablu (lijevo dijete, èvor, desno dijete)

	if (bst == NULL)
		return;

	PrintBSTree(bst->left);

	printf("%s \n", bst->word);

	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rijeè po rijeè iz stabla u tekstualnu datoteku. Rijeèi su odvojene razmakom.
	// Pre-order šetnja po stablu (ttenutni èvor pa djeca)

	if (bst == NULL)
		return;

	fprintf(fd, "%s ", bst->word);

	SaveBSTree(bst->left, fd);
	SaveBSTree(bst->right, fd);
}

void DeleteBSTree(BSTree bst)
{
	// Briše stablo (string word i sam èvor) iz memorije.
	// Post-order šetnja po stablu (prvo djeca pa trenutni èvor)

	if (bst == NULL) {
		return;
	}

	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);

	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE *fd)
{
	// Uèitava rijeè po rijeè iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rijeè duplicirati sa strdup().

	BSTree tree = NewBSTree();

	char word[100];

	while (fscanf(fd, "%s", word, 99) != EOF) {
		AddNode(&tree, _strdup(word));
	}

	return tree;
}
