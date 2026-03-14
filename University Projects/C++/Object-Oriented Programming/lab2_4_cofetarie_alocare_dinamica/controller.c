#define _CRT_SECURE_NO_WARNINGS
#include "controller.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cautare_materie(repo_materii* repo, char* nume, char* producator, int cantitate) {
	materie mat;
	mat.nume = nume;
	mat.producator = producator;
	mat.cantitate = cantitate;
	return cautare(repo, mat);
}

int adaugare_materie(repo_materii* repo, char* nume, char* producator, int cantitate) {
	materie mat;
	creeaza(nume, producator, cantitate, &mat);
	int error_code = adaugare(repo, mat);
	if (error_code <= 0) {
		distruge(&mat);
	}
	return error_code;

}

int stergere_materie(repo_materii* repo, char* nume, char* producator) {
	materie mat;
	mat.nume = nume;
	mat.producator = producator;
	return stergere(repo, mat);
}

int modificare_materie(repo_materii* repo, char* nume, char* producator, char* nume_nou, char* producator_nou, int cantitate_noua) {
	materie mat;
	mat.nume = nume;
	mat.producator = producator;
	return modificare(repo, mat, nume_nou, producator_nou, cantitate_noua);
}

materie* toate_materiile(repo_materii* repo) {
	return get_materii(repo);
}

int filtreaza_litera(repo_materii* repo, char litera, materie* lista_filtrata) {
	int nr = 0;
	for (int i = 0; i < repo->nr_materii; i++) {
		materie m = repo->lista[i];
		if (m.nume[0] == litera) {
			lista_filtrata[nr++] = repo->lista[i];
		}
	}
	return nr;
}

int filtreaza_cantitate(repo_materii* repo, int cantitate, materie* lista_filtrata) {
	int nr = 0;
	for (int i = 0; i < repo->nr_materii; i++) {
		materie m = repo->lista[i];
		if (m.cantitate < cantitate) {
			lista_filtrata[nr++] = repo->lista[i];
		}
	}
	return nr;
}

/*
* Functia returneaza o copie a listei transmise ca parametru
*/
materie* copy_list(materie* lista, int lungime) {
	if (lungime == 0)
		return NULL;
	materie* copy = (materie*)malloc(lungime * sizeof(materie));
	//if (copy == NULL) {
		//printf("Eroare la alocarea memoriei pentru copy_list!\n");
		//return NULL;
	//}
	if (copy != NULL) {
		for (int i = 0; i < lungime; i++) {
			//materie materie_copiata;
			creeaza(lista[i].nume, lista[i].producator, lista[i].cantitate, &copy[i]);
			//printf("Adresa lui copy[%d]: %p, nume: %p, producator: %p\n",
				//i, (void*)&copy[i], (void*)copy[i].nume, (void*)copy[i].producator);
			//printf("Nume: %s, Producator: %s, Cantitate: %d\n",
				//copy[i].nume, copy[i].producator, copy[i].cantitate);
			//copy[i] = materie_copiata;
		}
	}
	//printf("Pointer returnat de copy_list: %p\n", (void*)copy);
	return copy;
}

void destroy_list(materie* lista, int lungime) {
	for (int i = 0; i < lungime; i++) {
		distruge(&lista[i]);
	}
	free(lista);
}
