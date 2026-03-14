#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"

//Interfata ce defineste service-ul

/*
* Cauta materia in repo
* Returneaza 1 daca exista, 0 altfel
*/
int cautare_materie(repo_materii* repo, char nume[50], char producator[50]);

/*
* Adauga materia in repo
* Returneaza 1 daca s-a adaugat, 0 daca nu mai este spatiu, -1 daca numele este invalid, -2 daca producatorul este invalid,
* -3 daca cantitatea este invalida
*/
int adaugare_materie(repo_materii* repo, char nume[50], char producator[50], int cantitate);

/*
* Sterge o materie din repository
* Returneaza 1 daca s-a sters, 0 altfel
*/
int stergere_materie(repo_materii* repo, char nume[50], char producator[50]);

/*
* Returneaza lista de materii
*/
materie* toate_materiile(repo_materii* repo);

/*
* Modifica o materie din repository
* Returneaza 1 daca s-a modificat, 0 altfel
*/
int modificare_materie(repo_materii* repo, char nume[50], char producator[50], char nume_nou[50], char producator_nou[50], int cantitate_noua);

/*
* Filtreaza lista de materii care incep cu o litera data
* Returneaza numarul de materii gasite
*/
int filtreaza_litera(repo_materii* repo, char litera, materie lista_filtrata[]);

/*
* Filtreaza lista de materii care au cantitatea mai mica decat un numar dat
* Returneaza numarul de materii gasite
*/
int filtreaza_cantitate(repo_materii* repo, int cantitate, materie lista_filtrata[]);

/*
* Sorteaza lista de materii crescator dupa nume
* Returneaza lista sortata
*/
void sorteaza_nume(repo_materii* repo, materie* lista_sortata);

/*
* Sorteaza lista de materii crescator dupa cantitate
* Returneaza lista sortata
*/
void sorteaza_cantitate(repo_materii* repo, materie* lista_sortata);

#endif