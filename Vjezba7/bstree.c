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
	// Rekurzivno se tra�i mjesto za novi �vor u stablu. Ako rije� postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokaziva�.

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
	// Rekurzivno se prolazi cijelo stablo da bi se prona�la najdu�a grana (visina stabla).
	
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
	// Ispisuje rije�i u stablu na ekran po abecednom redu.
	// In-order �etnja po stablu (lijevo dijete, �vor, desno dijete)

	if (bst == NULL)
		return;

	PrintBSTree(bst->left);

	printf("%s \n", bst->word);

	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rije� po rije� iz stabla u tekstualnu datoteku. Rije�i su odvojene razmakom.
	// Pre-order �etnja po stablu (ttenutni �vor pa djeca)

	if (bst == NULL)
		return;

	fprintf(fd, "%s ", bst->word);

	SaveBSTree(bst->left, fd);
	SaveBSTree(bst->right, fd);
}

void DeleteBSTree(BSTree bst)
{
	// Bri�e stablo (string word i sam �vor) iz memorije.
	// Post-order �etnja po stablu (prvo djeca pa trenutni �vor)

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
	// U�itava rije� po rije� iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rije� duplicirati sa strdup().

	BSTree tree = NewBSTree();

	char word[100];

	while (fscanf(fd, "%s", word, 99) != EOF) {
		AddNode(&tree, _strdup(word));
	}

	return tree;
}
