#include "controller.h"
#include <stdio.h>


int cautare_materie(repo_materii* repo, char nume[50], char producator[50]) {
	return cautare(repo, nume, producator);
}

int adaugare_materie(repo_materii* repo, char nume[50], char producator[50], int cantitate) {
	return adaugare(repo, nume, producator, cantitate);
}

int stergere_materie(repo_materii* repo, char nume[50], char producator[50]) {
	return stergere(repo, nume, producator);
}

int modificare_materie(repo_materii* repo, char nume[50], char producator[50], char nume_nou[50], char producator_nou[50], int cantitate_noua) {
	return modificare(repo, nume, producator, nume_nou, producator_nou, cantitate_noua);
}

materie* toate_materiile(repo_materii* repo) {
	return get_materii(repo);
}

int filtreaza_litera(repo_materii* repo, char litera, materie lista_filtrata[]) {
	return filter_litera(repo, litera, lista_filtrata);
}

int filtreaza_cantitate(repo_materii* repo, int cantitate, materie lista_filtrata[]) {
	return filter_cantitate(repo, cantitate, lista_filtrata);
}

void sorteaza_nume(repo_materii* repo, materie* lista_sortata) {
	sort_nume(repo, lista_sortata);
}

void sorteaza_cantitate(repo_materii* repo, materie* lista_sortata) {
	sort_cantitate(repo, lista_sortata);
}