#include <assert.h>
#include <string.h>
#include "repository.h"
#include "controller.h"
#include "sort.h"

void test_init_repo() {
	repo_materii repo;
	init_repo(&repo);
	assert(repo.nr_materii == 0);
	distruge_repo(&repo);
	//printf("Test init_repo succeeded!\n");
}

void test_adaugare() {
	repo_materii repo;
	init_repo(&repo);
	materie mat;
	creeaza("cofeina", "jacobs", 100, &mat);
	assert(adaugare(&repo, mat) == 1);
	assert(strcmp(repo.lista[0].nume, "cofeina") == 0);
	assert(repo.nr_materii == 1);
	assert(adaugare(&repo, mat) == 1);
	assert(repo.lista[0].cantitate == 200);
	materie mat1, mat2, mat3;
	creeaza("", "borsec", 50, &mat1);
	creeaza("apa", "", 50, &mat2);
	creeaza("apa", "borsec", -5, &mat3);
	assert(adaugare(&repo, mat1) == -1);
	assert(adaugare(&repo, mat2) == -2);
	assert(adaugare(&repo, mat3) == -3);
	distruge(&mat1);
	distruge(&mat2);
	distruge(&mat3);
	distruge_repo(&repo);
	assert(adaugare(NULL, mat1) == 0);
	//printf("Test adaugare succeeded!\n");
}

void test_cautare() {
	repo_materii repo;
	init_repo(&repo);
	materie mat1, mat2;
	creeaza("cofeina", "jacobs", 100, &mat1);
	creeaza("lapte", "fulga", 50, &mat2);
	adaugare(&repo, mat1);
	assert(cautare(&repo, mat2) == -1);

	assert(are_equal(&mat2, NULL) == 0);
	assert(are_equal(NULL, NULL) == 1);

	assert(cautare(&repo, mat1) == 0);
	distruge(&mat2);
	distruge_repo(&repo);
	//printf("Test cautare succeeded!\n");
}

void test_stergere() {
	repo_materii repo;
	init_repo(&repo);
	materie mat1, mat2, mat3;
	creeaza("cofeina", "jacobs", 100, &mat1);
	creeaza("lapte", "fulga", 50, &mat2);
	creeaza("apa", "borsec", 150, &mat3);
	adaugare(&repo, mat1);
	assert(stergere(&repo, mat2) == 0);
	assert(repo.nr_materii == 1);
	adaugare(&repo, mat2);
	adaugare(&repo, mat3);
	assert(stergere(&repo, mat1) == 1);
	assert(repo.nr_materii == 2);
	distruge_repo(&repo);
	//printf("Test stergere succeeded!\n");
}

void test_modificare() {
	repo_materii repo;
	init_repo(&repo);
	materie mat1, mat2;
	creeaza("cofeina", "jacobs", 100, &mat1);
	creeaza("lapte", "fulga", 50, &mat2);
	adaugare(&repo, mat1);
	assert(modificare(&repo, mat2, "bere", "heineken", 100) == 0);

	assert(modificare(&repo, mat1, "lapte", "fulga", 50) == 1);

	assert(strcmp(repo.lista[0].nume, "lapte") == 0);

	distruge(&mat2);
	distruge_repo(&repo);
	//printf("Test modificare succeeded!\n");
}

void test_get_materii() {
	repo_materii repo;
	init_repo(&repo);
	materie mat;
	creeaza("cofeina", "jacobs", 100, &mat);
	adaugare(&repo, mat);
	materie* l = get_materii(&repo);
	assert(strcmp(l[0].nume, "cofeina") == 0);
	distruge_repo(&repo);
	//printf("Test get_materii succeeded!\n");
}

void repo_tests() {
	test_init_repo();
	test_adaugare();
	test_stergere();
	test_modificare();
	test_cautare();
	test_get_materii();
	//printf("\nAll repo tests succeeded!\n");
}

void test_cautare_service() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	assert(cautare_materie(&repo, "lapte", "fulga", 50) == -1);

	assert(cautare_materie(&repo, "cofeina", "jacobs", 100) == 0);
	distruge_repo(&repo);
	//printf("Test cautare_service succeeded!\n");
}

void test_adaugare_service() {
	repo_materii repo;
	init_repo(&repo);
	assert(adaugare_materie(&repo, "cofeina", "jacobs", 100) == 1);
	assert(strcmp(repo.lista[0].nume, "cofeina") == 0);
	assert(adaugare_materie(&repo, "", "furdui", 10) == -1);
	assert(repo.nr_materii == 1);
	distruge_repo(&repo);
	//printf("Test adaugare_service succeeded!\n");
}

void test_stergere_service() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	assert(stergere_materie(&repo, "lapte", "fulga") == 0);
	assert(repo.nr_materii == 1);

	assert(stergere_materie(&repo, "cofeina", "jacobs") == 1);
	assert(repo.nr_materii == 0);

	distruge_repo(&repo);

	//printf("Test stergere_service succeeded!\n");
}

void test_modificare_service() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	assert(modificare_materie(&repo, "lapte", "fulga", "bere", "heineken", 100) == 0);

	assert(modificare_materie(&repo, "cofeina", "jacobs", "lapte", "fulga", 50) == 1);

	distruge_repo(&repo);

	//printf("Test modificare_service succeeded!\n");
}

void test_toate_materiile() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	materie* l = toate_materiile(&repo);
	assert(strcmp(l[0].nume, "cofeina") == 0);
	distruge_repo(&repo);
	//printf("Test toate_materiile succeeded!\n");
}

void test_filtreaza_litera() {
	repo_materii repo;
	init_repo(&repo);
	materie mat1, mat2, mat3;
	creeaza("cofeina", "jacobs", 100, &mat1);
	creeaza("cartofi", "piata", 50, &mat2);
	creeaza("apa", "bucovina", 90, &mat3);
	adaugare(&repo, mat1);
	adaugare(&repo, mat2);
	adaugare(&repo, mat3);
	materie lista_filtrata[MAX_MATERII];
	assert(filtreaza_litera(&repo, 'z', lista_filtrata) == 0);
	assert(filtreaza_litera(&repo, 'a', lista_filtrata) == 1);
	assert(filtreaza_litera(&repo, 'c', lista_filtrata) == 2);
	distruge_repo(&repo);
	//printf("Test filter_litera succeeded!\n");
}

void test_filtreaza_cantitate() {
	repo_materii repo;
	init_repo(&repo);
	materie mat1, mat2, mat3;
	creeaza("cofeina", "jacobs", 100, &mat1);
	creeaza("cartofi", "piata", 50, &mat2);
	creeaza("apa", "bucovina", 90, &mat3);
	adaugare(&repo, mat1);
	adaugare(&repo, mat2);
	adaugare(&repo, mat3);
	materie lista_filtrata[MAX_MATERII];
	assert(filtreaza_cantitate(&repo, 95, lista_filtrata) == 2);
	assert(filtreaza_cantitate(&repo, 200, lista_filtrata) == 3);
	assert(filtreaza_cantitate(&repo, 40, lista_filtrata) == 0);
	distruge_repo(&repo);
	//printf("Test filter_cantitate succeeded!\n");
}

void test_sorteaza_nume() {
	repo_materii repo;
	init_repo(&repo);
	materie mat1, mat2, mat3;
	creeaza("cofeina", "jacobs", 100, &mat1);
	creeaza("cartofi", "piata", 50, &mat2);
	creeaza("apa", "bucovina", 90, &mat3);
	adaugare(&repo, mat1);
	adaugare(&repo, mat2);
	adaugare(&repo, mat3);
	materie* lista_sortata = sorteaza(&repo, compara_nume, 1);
	assert(strcmp(lista_sortata[0].nume, "apa") == 0);
	assert(strcmp(lista_sortata[1].nume, "cartofi") == 0);
	assert(strcmp(lista_sortata[2].nume, "cofeina") == 0);
	destroy_list(lista_sortata, repo.nr_materii);
	lista_sortata = sorteaza(&repo, compara_nume, 0);
	assert(strcmp(lista_sortata[2].nume, "apa") == 0);
	assert(strcmp(lista_sortata[1].nume, "cartofi") == 0);
	assert(strcmp(lista_sortata[0].nume, "cofeina") == 0);
	destroy_list(lista_sortata, repo.nr_materii);
	stergere(&repo, mat1);
	stergere(&repo, mat2);
	stergere(&repo, mat3);
	assert(sorteaza(&repo, compara_nume, 1) == NULL);
	assert(copy_list(repo.lista, 0) == NULL);
	distruge_repo(&repo);
	//printf("Test sorteaza_nume succeeded!\n");
}

void test_sorteaza_cantitate() {
	repo_materii repo;
	init_repo(&repo);
	materie mat1, mat2, mat3;
	creeaza("cofeina", "jacobs", 100, &mat1);
	creeaza("cartofi", "piata", 90, &mat2);
	creeaza("apa", "bucovina", 50, &mat3);
	adaugare(&repo, mat1);
	adaugare(&repo, mat2);
	adaugare(&repo, mat3);
	materie* lista_sortata = sorteaza(&repo, compara_cantitate, 1);
	assert(strcmp(lista_sortata[0].nume, "apa") == 0);
	assert(strcmp(lista_sortata[1].nume, "cartofi") == 0);
	assert(strcmp(lista_sortata[2].nume, "cofeina") == 0);
	destroy_list(lista_sortata, repo.nr_materii);
	lista_sortata = sorteaza(&repo, compara_cantitate, 0);
	assert(strcmp(lista_sortata[2].nume, "apa") == 0);
	assert(strcmp(lista_sortata[1].nume, "cartofi") == 0);
	assert(strcmp(lista_sortata[0].nume, "cofeina") == 0);
	destroy_list(lista_sortata, repo.nr_materii);
	stergere(&repo, mat1);
	stergere(&repo, mat2);
	stergere(&repo, mat3);
	assert(sorteaza(&repo, compara_cantitate, 1) == NULL);
	distruge_repo(&repo);
	//printf("Test sorteaza_cantitate succeeded!\n");
}

void controller_tests() {
	test_adaugare_service();
	test_stergere_service();
	test_modificare_service();
	test_cautare_service();
	test_toate_materiile();
	test_filtreaza_litera();
	test_filtreaza_cantitate();
	test_sorteaza_nume();
	test_sorteaza_cantitate();
	//printf("\nAll service tests succeeded!\n");
}
