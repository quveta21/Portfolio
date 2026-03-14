#define _CRT_SECURE_NO_WARNINGS
#include "materie.h"
#include <string.h>
#include <stdlib.h>


void creeaza(char* nume, char* producator, int cantitate, materie* mat) {
	mat->nume = (char*)malloc(strlen(nume) + 1);
	if (mat->nume != NULL)
		strcpy_s(mat->nume, strlen(nume) + 1, nume);
	mat->producator = (char*)malloc(strlen(producator) + 1);
	if (mat->producator != NULL)
		strcpy_s(mat->producator, strlen(producator) + 1, producator);
	mat->cantitate = cantitate;
}

void distruge(materie* mat) {
	free(mat->nume);
	free(mat->producator);
}

int are_equal(materie* m1, materie* m2) {
	if (m1 == NULL && m2 == NULL)
		return 1;
	if (m1 == NULL || m2 == NULL)
		return 0;
	return strcmp(m1->nume, m2->nume) == 0 && strcmp(m1->producator, m2->producator) == 0;
}