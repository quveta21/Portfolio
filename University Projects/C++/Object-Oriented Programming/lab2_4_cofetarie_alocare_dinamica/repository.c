#define _CRT_SECURE_NO_WARNINGS
#include "repository.h"
#include <string.h>
#include <stdlib.h>

void init_repo(repo_materii* repo) {
	repo->nr_materii = 0;
	repo->capacitate = 1;
	repo->lista = (materie*)malloc(repo->capacitate * sizeof(materie));
}

void asigura_capacitatea(repo_materii* repo) {
	if (repo->nr_materii >= repo->capacitate) {
		int capacitate_noua = repo->capacitate * 2; //la fiecare overflow se dubleaza capacitatea
		materie* lista_noua = (materie*)realloc(repo->lista, capacitate_noua * sizeof(materie));
		repo->lista = lista_noua;
		repo->capacitate = capacitate_noua;
	}
}

void distruge_repo(repo_materii* repo) {
	for (int i = 0; i < repo->nr_materii; i++) {
		materie m = repo->lista[i];
		distruge(&m);
	}
	repo->nr_materii = 0;
	free(repo->lista);
}

/*
*	Functie care valideaza numele, returneaza 1 daca e valid, 0 altfel
*/
int validare_nume(char* nume) {
	return strlen(nume) > 0 && strcmp(nume, "\n") != 0;
}

/*
*	Functie care valideaza producatorul, returneaza 1 daca e valid, 0 altfel
*/
int validare_producator(char* producator) {
	return strlen(producator) > 0 && strcmp(producator, "\n") != 0;
}

/*
*	Functie care valideaza cantitate, returneaza 1 daca e valid, 0 altfel
*/
int validare_cantitate(int cantitate) {
	return cantitate > 0;
}

int cautare(repo_materii* repo, materie mat) {
	for (int i = 0; i < repo->nr_materii; ++i) {
		if (are_equal(&mat, &repo->lista[i]))
			return i;
	}
	return -1;
}

int adaugare(repo_materii* repo, materie mat) {
	if (!validare_nume(mat.nume))
		return -1;
	if (!validare_producator(mat.producator))
		return -2;
	if (!validare_cantitate(mat.cantitate))
		return -3;
	if (repo == NULL)
		return 0;
	asigura_capacitatea(repo);
	int poz = cautare(repo, mat);
	if (poz != -1) {
		repo->lista[poz].cantitate += mat.cantitate;
		return 1;
	}
	repo->lista[repo->nr_materii++] = mat;
	return 1;
}

int stergere(repo_materii* repo, materie mat) {
	int poz = cautare(repo, mat);
	if (poz >= 0) {
		distruge(&repo->lista[poz]);
		for (int i = poz; i < repo->nr_materii - 1; i++)
			repo->lista[i] = repo->lista[i + 1];
		repo->nr_materii--;
		return 1;
	}
	return 0;
}

int modificare(repo_materii* repo, materie mat, char* nume_nou, char* producator_nou, int cantitate_noua) {
	/*
	if (!validare_nume(nume_nou))
		return -1;
	if (!validare_producator(producator_nou))
		return -2;
	if (!validare_cantitate(cantitate_noua))
		return -3;
	if (repo == NULL)
		return 0;
		*/
	int poz = cautare(repo, mat);
	if (poz >= 0) {
		char* mat_nume_nou = (char*)realloc(repo->lista[poz].nume, strlen(nume_nou) + 1);
		repo->lista[poz].nume = mat_nume_nou;
		strcpy_s(repo->lista[poz].nume, strlen(nume_nou) + 1, nume_nou);
		
		char* mat_producator_nou = (char*)realloc(repo->lista[poz].producator, strlen(producator_nou) + 1);
		repo->lista[poz].producator = mat_producator_nou;
		strcpy_s(repo->lista[poz].producator, strlen(producator_nou) + 1, producator_nou);

		repo->lista[poz].cantitate = cantitate_noua;
		return 1;
	}
	return 0;
}

materie* get_materii(repo_materii* repo) {
	return repo->lista;
}