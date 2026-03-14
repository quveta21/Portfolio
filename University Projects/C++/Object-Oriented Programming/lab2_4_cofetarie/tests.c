#include <assert.h>
#include <string.h>
#include "repository.h"
#include "controller.h"

void test_init_repo() {
	repo_materii repo;
	init_repo(&repo);
	assert(repo.nr_materii == 0);
	//printf("Test init_repo succeeded!\n");
}

void test_adaugare() {
	repo_materii repo;
	init_repo(&repo);
	assert(adaugare(&repo, "cofeina", "jacobs", 100) == 1);
	assert(strcmp(repo.lista[0].nume, "cofeina") == 0);
	assert(repo.nr_materii == 1);
	assert(adaugare(&repo, "cofeina", "jacobs", 100) == 1);
	assert(repo.lista[0].cantitate == 200);
	assert(adaugare(&repo, "", "borsec", 50) == -1);
	assert(adaugare(&repo, "apa", "", 50) == -2);
	assert(adaugare(&repo, "apa", "borsec", -5) == -3);
	repo.nr_materii = MAX_MATERII;
	assert(adaugare(&repo, "zahar", "furdui", 75) == 0);
	//printf("Test adaugare succeeded!\n");
}

void test_cautare() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	assert(cautare(&repo, "lapte", "fulga") == -1);

	assert(cautare(&repo, "cofeina", "jacobs") == 0);
	//printf("Test cautare succeeded!\n");
}

void test_stergere() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	assert(stergere(&repo, "lapte", "fulga") == 0);
	assert(repo.nr_materii == 1);
	adaugare(&repo, "lapte", "fulga", 50);
	adaugare(&repo, "apa", "borsec", 150);
	assert(stergere(&repo, "cofeina", "jacobs") == 1);
	assert(repo.nr_materii == 2);

	//printf("Test stergere succeeded!\n");
}

void test_modificare() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	assert(modificare(&repo, "lapte", "fulga", "bere", "heineken", 100) == 0);
	
	assert(modificare(&repo, "cofeina", "jacobs", "lapte", "fulga", 50) == 1);

	//printf("Test modificare succeeded!\n");
}

void test_get_materii() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	materie* l = get_materii(&repo);
	assert(strcmp(l[0].nume, "cofeina") == 0);
	//printf("Test get_materii succeeded!\n");
}

void test_filter_litera() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	adaugare(&repo, "cartofi", "piata", 50);
	adaugare(&repo, "apa", "bucovina", 90);
	materie lista_filtrata[MAX_MATERII];
	assert(filter_litera(&repo, 'z', lista_filtrata) == 0);
	assert(filter_litera(&repo, 'a', lista_filtrata) == 1);
	assert(filter_litera(&repo, 'c', lista_filtrata) == 2);

	//printf("Test filter_litera succeeded!\n");
}

void test_filter_cantitate() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	adaugare(&repo, "cartofi", "piata", 50);
	adaugare(&repo, "apa", "bucovina", 90);
	materie lista_filtrata[MAX_MATERII];
	assert(filter_cantitate(&repo, 95, lista_filtrata) == 2);
	assert(filter_cantitate(&repo, 200, lista_filtrata) == 3);
	assert(filter_cantitate(&repo, 40, lista_filtrata) == 0);
	//printf("Test filter_cantitate succeeded!\n");
}
void test_sort_nume() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	adaugare(&repo, "cartofi", "piata", 50);
	adaugare(&repo, "apa", "bucovina", 90);
	materie lista_sortata[MAX_MATERII];
	sort_nume(&repo, lista_sortata);
	assert(strcmp(lista_sortata[0].nume, "apa") == 0);
	assert(strcmp(lista_sortata[1].nume, "cartofi") == 0);
	assert(strcmp(lista_sortata[2].nume, "cofeina") == 0);
	printf("Test sort_nume succeeded!\n");
}

void test_sort_cantitate() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	adaugare(&repo, "cartofi", "piata", 50);
	adaugare(&repo, "apa", "bucovina", 90);
	materie lista_sortata[MAX_MATERII];
	sort_cantitate(&repo, lista_sortata);
	assert(lista_sortata[0].cantitate == 50);
	assert(lista_sortata[1].cantitate == 90);
	assert(lista_sortata[2].cantitate == 100);
	printf("Test sort_cantitate succeeded!\n");
}

void repo_tests() {
	test_init_repo();
	test_adaugare();
	test_stergere();
	test_modificare();
	test_cautare();
	test_get_materii();
	test_filter_litera();
	test_filter_cantitate();
	test_sort_nume();
	test_sort_cantitate();
	printf("\nAll repo tests succeeded!\n");
}

void test_cautare_service() {
	repo_materii repo;
	init_repo(&repo);
	adaugare(&repo, "cofeina", "jacobs", 100);
	assert(cautare_materie(&repo, "lapte", "fulga") == -1);

	assert(cautare_materie(&repo, "cofeina", "jacobs") == 0);
	//printf("Test cautare_service succeeded!\n");
}

void test_adaugare_service() {
	repo_materii repo;
	init_repo(&repo);
	assert(adaugare_materie(&repo, "cofeina", "jacobs", 100) == 1);
	assert(strcmp(repo.lista[0].nume, "cofeina") == 0);
	assert(repo.nr_materii == 1);
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

	//printf("Test stergere_service succeeded!\n");
}

void test_modificare_service() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	assert(modificare_materie(&repo, "lapte", "fulga", "bere", "heineken", 100) == 0);

	assert(modificare_materie(&repo, "cofeina", "jacobs", "lapte", "fulga", 50) == 1);

	//printf("Test modificare_service succeeded!\n");
}

void test_toate_materiile() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	materie* l = toate_materiile(&repo);
	assert(strcmp(l[0].nume, "cofeina") == 0);
	//printf("Test toate_materiile succeeded!\n");
}

void test_filtreaza_litera() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	adaugare_materie(&repo, "cartofi", "piata", 50);
	adaugare_materie(&repo, "apa", "bucovina", 90);
	materie lista_filtrata[MAX_MATERII];
	assert(filtreaza_litera(&repo, 'z', lista_filtrata) == 0);
	assert(filtreaza_litera(&repo, 'a', lista_filtrata) == 1);
	assert(filtreaza_litera(&repo, 'c', lista_filtrata) == 2);

	//printf("Test filtreaza_litera succeeded!\n");
}

void test_filtreaza_cantitate() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	adaugare_materie(&repo, "cartofi", "piata", 50);
	adaugare_materie(&repo, "apa", "bucovina", 90);
	materie lista_filtrata[MAX_MATERII];
	assert(filtreaza_cantitate(&repo, 95, lista_filtrata) == 2);
	assert(filtreaza_cantitate(&repo, 200, lista_filtrata) == 3);
	assert(filtreaza_cantitate(&repo, 40, lista_filtrata) == 0);
	//printf("Test filtreaza_cantitate succeeded!\n");
}

void test_sorteaza_nume() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	adaugare_materie(&repo, "cartofi", "piata", 50);
	adaugare_materie(&repo, "apa", "bucovina", 90);
	materie lista_sortata[MAX_MATERII];
	sorteaza_nume(&repo, lista_sortata);
	assert(strcmp(lista_sortata[0].nume, "apa") == 0);
	assert(strcmp(lista_sortata[1].nume, "cartofi") == 0);
	assert(strcmp(lista_sortata[2].nume, "cofeina") == 0);
	printf("Test sorteaza_nume succeeded!\n");
}

void test_sorteaza_cantitate() {
	repo_materii repo;
	init_repo(&repo);
	adaugare_materie(&repo, "cofeina", "jacobs", 100);
	adaugare_materie(&repo, "cartofi", "piata", 50);
	adaugare_materie(&repo, "apa", "bucovina", 90);
	materie lista_sortata[MAX_MATERII];
	sorteaza_cantitate(&repo, lista_sortata);
	assert(lista_sortata[0].cantitate == 50);
	assert(lista_sortata[1].cantitate == 90);
	assert(lista_sortata[2].cantitate == 100);
	printf("Test sorteaza_cantitate succeeded!\n");
}

void controller_tests() {
	test_init_repo();
	test_adaugare_service();
	test_stergere_service();
	test_modificare_service();
	test_cautare_service();
	test_toate_materiile();
	test_filtreaza_litera();
	test_filtreaza_cantitate();
	test_sorteaza_nume();
	test_sorteaza_cantitate();
	printf("\nAll service tests succeeded!\n");
}
