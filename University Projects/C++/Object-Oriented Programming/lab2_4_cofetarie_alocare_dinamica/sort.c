#include "sort.h"
#include "controller.h"
#include <string.h>

int compara_nume(materie mat1, materie mat2) {
	if (strcmp(mat1.nume, mat2.nume) >= 0)
		return 1;
	return 2;
}

int compara_cantitate(materie mat1, materie mat2) {
	if (mat1.cantitate >= mat2.cantitate)
		return 1;
	return 2;
}

materie* sorteaza(repo_materii* repo, CompareFunction comparare, int ascending) {
	if (repo->nr_materii == 0)
		return NULL;
	materie* lista_sortata = copy_list(repo->lista, repo->nr_materii);
	int sorted = 0;
	while (!sorted) {
		sorted = 1;
		for (int i = 0; i < repo->nr_materii - 1; i++) {
			if ((comparare(lista_sortata[i], lista_sortata[i + 1]) == 1 && ascending) ||
				(comparare(lista_sortata[i], lista_sortata[i + 1]) == 2 && !ascending)) {
				materie aux = lista_sortata[i];
				lista_sortata[i] = lista_sortata[i + 1];
				lista_sortata[i + 1] = aux;
				sorted = 0;
			}
		}
	}
	return lista_sortata;
}