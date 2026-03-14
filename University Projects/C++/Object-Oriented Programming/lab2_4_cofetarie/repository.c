#define _CRT_SECURE_NO_WARNINGS
#include "repository.h"
#include <string.h>

void init_repo(repo_materii* repo) {
	repo->nr_materii = 0;
}

/*
*	Functie care valideaza numele, returneaza 1 daca e valid, 0 altfel
*/
int validare_nume(char nume[50]) {
	return strlen(nume) > 0 && strcmp(nume, "\n") != 0;
}

/*
*	Functie care valideaza producatorul, returneaza 1 daca e valid, 0 altfel
*/
int validare_producator(char producator[50]) {
	return strlen(producator) > 0 && strcmp(producator, "\n") != 0;
}

/*
*	Functie care valideaza cantitate, returneaza 1 daca e valid, 0 altfel
*/
int validare_cantitate(int cantitate) {
	return cantitate > 0;
}

int cautare(repo_materii* repo, char nume[50], char producator[50]) {
	for (int i = 0; i < repo->nr_materii; ++i) {
		if (strcmp(repo->lista[i].nume, nume) == 0 && strcmp(repo->lista[i].producator, producator) == 0)
			return i;
	}
	return -1;
}

int adaugare(repo_materii* repo, char nume[50], char producator[50], int cantitate) {
	if (!validare_nume(nume))
		return -1;
	if (!validare_producator(producator))
		return -2;
	if (!validare_cantitate(cantitate))
		return -3;
	if (repo->nr_materii >= MAX_MATERII)
		return 0;
	int poz = cautare(repo, nume, producator);
	if (poz == -1) {
			repo->lista[repo->nr_materii] = creeaza(nume, producator, cantitate);
			repo->nr_materii++;
			return 1; }
	else {
		repo->lista[poz].cantitate += cantitate;
		return 1;
	}
}

int stergere(repo_materii* repo, char nume[50], char producator[50]) {
	int poz = cautare(repo, nume, producator);
	if (poz >= 0) {
		for (int i = poz; i < repo->nr_materii - 1; i++)
			repo->lista[i] = repo->lista[i + 1];
		repo->nr_materii--;
		return 1; }
	else {
		return 0;
	}
}

int modificare(repo_materii* repo, char nume[50], char producator[50], char nume_nou[50], char producator_nou[50], int cantitate_noua) {
	int poz = cautare(repo, nume, producator);
	if (poz >= 0) {
		strcpy(repo->lista[poz].nume, nume_nou);
		strcpy(repo->lista[poz].producator, producator_nou);
		repo->lista[poz].cantitate = cantitate_noua;
		return 1; }
	else
		return 0;
}

materie* get_materii(repo_materii* repo) {
	return repo->lista;
}

int filter_litera(repo_materii* repo, char litera, materie lista_filtrata[]) {
	int nr = 0;
	for (int i = 0; i < repo->nr_materii; i++) {
		materie m = repo->lista[i];
		if (m.nume[0] == litera) {
			lista_filtrata[nr++] = repo->lista[i];
		}
	}
	return nr;
}

int filter_cantitate(repo_materii* repo, int cantitate, materie lista_filtrata[]) {
	int nr = 0;
	for (int i = 0; i < repo->nr_materii; i++) {
		materie m = repo->lista[i];
		if (m.cantitate < cantitate) {
			lista_filtrata[nr++] = repo->lista[i];
		}
	}
	return nr;
}

void sort_nume(repo_materii* repo, materie* lista_sortata) {
	for (int i = 0; i < repo->nr_materii; i++) {
		strcpy(lista_sortata[i].nume, repo->lista[i].nume);
		strcpy(lista_sortata[i].producator, repo->lista[i].producator);
		lista_sortata[i].cantitate = repo->lista[i].cantitate;
	}
	for (int i = 0; i < repo->nr_materii-1; i++)
		for(int j = i+1; j < repo->nr_materii; j++)
			if (strcmp(lista_sortata[i].nume, lista_sortata[j].nume) > 0) {
				char aux[50];
				int auxi;
				strcpy(aux, lista_sortata[i].nume);
				strcpy(lista_sortata[i].nume, lista_sortata[j].nume);
				strcpy(lista_sortata[j].nume, aux);

				strcpy(aux, lista_sortata[i].producator);
				strcpy(lista_sortata[i].producator, lista_sortata[j].producator);
				strcpy(lista_sortata[j].producator, aux);

				auxi = lista_sortata[i].cantitate;
				lista_sortata[i].cantitate = lista_sortata[j].cantitate;
				lista_sortata[j].cantitate = auxi;
			}
}

void sort_cantitate(repo_materii* repo, materie* lista_sortata) {
	for (int i = 0; i < repo->nr_materii; i++) {
		strcpy(lista_sortata[i].nume, repo->lista[i].nume);
		strcpy(lista_sortata[i].producator, repo->lista[i].producator);
		lista_sortata[i].cantitate = repo->lista[i].cantitate;
	}
	for (int i = 0; i < repo->nr_materii - 1; i++)
		for (int j = i + 1; j < repo->nr_materii; j++)
			if (lista_sortata[i].cantitate > lista_sortata[j].cantitate) {
				char aux[50];
				int auxi;
				strcpy(aux, lista_sortata[i].nume);
				strcpy(lista_sortata[i].nume, lista_sortata[j].nume);
				strcpy(lista_sortata[j].nume, aux);

				strcpy(aux, lista_sortata[i].producator);
				strcpy(lista_sortata[i].producator, lista_sortata[j].producator);
				strcpy(lista_sortata[j].producator, aux);

				auxi = lista_sortata[i].cantitate;
				lista_sortata[i].cantitate = lista_sortata[j].cantitate;
				lista_sortata[j].cantitate = auxi;
			}
}
