#ifndef REPO_H
#define REPO_H

#include "materie.h"

//Interfata ce defineste repository-ul

typedef struct {
	materie* lista;
	int nr_materii;
	int capacitate;
}repo_materii;


/*
* Initializeaza repository-ul cu 0 materii
*/
void init_repo(repo_materii* repo);

/*
* Mareste capacitatea repository-ului in caz de overflow
*/
void asigura_capacitatea(repo_materii* repo);

/*
* Elibereaza memoria ocupata de repository
*/
void distruge_repo(repo_materii* repo);

/*
* Cauta existenta unei materii dupa nume si producator
* Returneaza pozitia lui in repository (index de la 0) daca exista, -1 altfel
*/
int cautare(repo_materii* repo, materie mat);

/*
* Adauga o materie in repository
* Returneaza 1 daca s-a adaugat, 0 daca nu mai este spatiu, -1 daca numele este invalid, -2 daca producatorul este invalid,
* -3 daca cantitatea este invalida
*/
int adaugare(repo_materii* repo, materie mat);

/*
* Sterge o materie din repository
* Returneaza 1 daca s-a sters, 0 altfel
*/
int stergere(repo_materii* repo, materie mat);

/*
* Returneaza lista de materii
*/
materie* get_materii(repo_materii* repo);

/*
* Modifica o materie din repository
* Returneaza 1 daca s-a modificat, 0 altfel
*/
int modificare(repo_materii* repo, materie mat, char* nume_nou, char* producator_nou, int cantitate_noua);

#endif