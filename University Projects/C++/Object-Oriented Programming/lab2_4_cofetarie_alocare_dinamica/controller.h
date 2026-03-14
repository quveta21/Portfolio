#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"

//Interfata ce defineste service-ul

/*
* Cauta materia in repo
* Returneaza 1 daca exista, 0 altfel
*/
int cautare_materie(repo_materii* repo, char* nume, char* producator, int cantitate);

/*
* Adauga materia in repo
* Returneaza 1 daca s-a adaugat, 0 daca nu mai este spatiu, -1 daca numele este invalid, -2 daca producatorul este invalid,
* -3 daca cantitatea este invalida
*/
int adaugare_materie(repo_materii* repo, char* nume, char* producator, int cantitate);

/*
* Sterge o materie din repository
* Returneaza 1 daca s-a sters, 0 altfel
*/
int stergere_materie(repo_materii* repo, char* nume, char* producator);

/*
* Returneaza lista de materii
*/
materie* toate_materiile(repo_materii* repo);

/*
* Modifica o materie din repository
* Returneaza 1 daca s-a modificat, 0 altfel
*/
int modificare_materie(repo_materii* repo, char* nume, char* producator, char* nume_nou, char* producator_nou, int cantitate_noua);

/*
* Filtreaza lista de materii care incep cu o litera data
* Returneaza numarul de materii gasite
*/
int filtreaza_litera(repo_materii* repo, char litera, materie* lista_filtrata);

/*
* Filtreaza lista de materii care au cantitatea mai mica decat un numar dat
* Returneaza numarul de materii gasite
*/
int filtreaza_cantitate(repo_materii* repo, int cantitate, materie* lista_filtrata);


/*
* Functie care face o copie la o lista de materii si returneaza pointerul spre acea lista
*/
materie* copy_list(materie* lista, int lungime);

/*
* Functie care distruge o lista de materii
*/
void destroy_list(materie* lista, int lungime);

#endif