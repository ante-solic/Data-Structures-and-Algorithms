#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

/*int mystrlen(char* word) {
	int i;

	for (i = 0; i < word[i]!='\0'; i++)
	;

	return i;
}
*/

/*
void mystrcpy(char* word, char* word2) {
	for (int i = 0; word[i] != '\0'; i++)
	{
		word[i] = word2[i];
	}

	printf("%s", word);
}
*/

/*
int mystrcmp(char* word, char* word2) {
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (word[i] > word2[i])
			return 1;
		else if (word[i] < word2[i])
			return -1;
		else if (word[i + 1] == '\0' && word2[i + 1] == '\0')
			return 0;
		else if (word[i + 1] != '\0'&& word2[i + 1] == '\0')
			return 1;
		else if (word[i + 1] == '\0'&& word2[i + 1] != '\0')
			return -1;
	}
}
*/

/*
void mystrcat(char* word, char* word2) {

	int n = 0;

	for (int i = 0; word[i] != '\0'; i++)
	{
		word[i] = word[i];
		n++;
	}

	for (int j = 0; word2[j] != '\0'; j++, n++)
		word[n] = word2[j];

	word[n + 1] = '\0';

	printf("%s", word);

}
*/

/*
int* mystrstr(const char *word, const char *word2) {
	char* s1, *s2, *s3;
	int i = 0, j = 0;
	s1 = word;
	s2 = word2;

	for (i = 0; i < strlen(word); i++)
	{
		s3 = s1;
			for (j = 0; j < strlen(word2); j++)
			{
				if (*s3 == *s2)
				{
					s3++;
					s2++;
				}
				else
					break;
			}
			s2 = word2;
			if (j == strlen(word2))
			{
				return s1;
			}
		s1++;
	}
	return NULL;
}
*/

void reverse(char* word, const char* word2) {

	int i = strlen(word);

	for (int j = strlen(word2) - 1; j >= 0; j--, i++) {
		word[i] = word2[j];
	}
	word[i++] = '\0';

	printf("%s", word);
}


int main() {
	char word[] = "Hello world!";

	//int* n = mystrlen(word);
	//printf("%d", n);

	char word2[] = "Hello";

	//mystrcpy(word, word2);

	//printf("%d", mystrcmp(word, word2));

	//mystrcat(word, word2);

	//int* p = mystrstr(word, word2, strlen(word), strlen(word2));

	//printf("%s", p);

	reverse(word, word2);

	return 0;
}