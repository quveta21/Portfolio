#ifndef REPO_H
#define REPO_H

#include "materie.h"

//Interfata ce defineste repository-ul

typedef struct {
	materie lista[MAX_MATERII];
	int nr_materii;
}repo_materii;


/*
* Initializeaza repository-ul cu 0 materii
*/
void init_repo(repo_materii* repo);

/*
* Cauta existenta unei materii dupa nume si producator
* Returneaza pozitia lui in repository (index de la 0) daca exista, -1 altfel
*/
int cautare(repo_materii* repo, char nume[50], char producator[50]);

/*
* Adauga o materie in repository
* Returneaza 1 daca s-a adaugat, 0 daca nu mai este spatiu, -1 daca numele este invalid, -2 daca producatorul este invalid,
* -3 daca cantitatea este invalida
*/
int adaugare(repo_materii* repo, char nume[50], char producator[50], int cantitate);

/*
* Sterge o materie din repository
* Returneaza 1 daca s-a sters, 0 altfel
*/
int stergere(repo_materii* repo, char nume[50], char producator[50]);

/*
* Returneaza lista de materii
*/
materie* get_materii(repo_materii* repo);

/*
* Modifica o materie din repository
* Returneaza 1 daca s-a modificat, 0 altfel
*/
int modificare(repo_materii* repo, char nume[50], char producator[50], char nume_nou[50], char producator_nou[50], int cantitate_noua);

/*
* Filtreaza lista de materii care incep cu o litera data
* Returneaza numarul de materii gasite
*/
int filter_litera(repo_materii* repo, char litera, materie lista_filtrata[]);

/*
* Filtreaza lista de materii care au cantitatea mai mica decat un numar dat
* Returneaza numarul de materii gasite
*/
int filter_cantitate(repo_materii* repo, int cantitate, materie lista_filtrata[]);

/*
* Sorteaza lista de materii crescator dupa nume
* Returneaza lista sortata
*/
void sort_nume(repo_materii* repo, materie* lista_sortata);

/*
* Sorteaza lista de materii crescator dupa cantitate
* Returneaza lista sortata
*/
void sort_cantitate(repo_materii* repo, materie* lista_sortata);

#endif