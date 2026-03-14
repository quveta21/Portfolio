#ifndef UI_H
#define UI_H

#include "controller.h"
#include "sort.h"

//Interfata utilizatorului

/*
* Functie care citeste input-ul utilizatorului si verifica daca e numar natural
* :param nr: referinta catre numarul citit
* :return: 1 (daca numarul e intreg) / 0 (in caz contrar)
*/
int int_valid(int* nr);

/*
* Preia de la utilizator un nume, un producator si o cantitate
* Returneaza 1 daca datele au fost introduse corect, 0 altfel
*/
int input(char* nume, char* producator, int* cantitate);

/*
* Ia input-ul utilizatorului si il adauga la lista de materii
*/
void ui_adaugare(repo_materii* repo);

/*
* Ia input-ul utilizatorului si modifica materia din lista cu datele introduse
*/
void ui_modificare(repo_materii* repo);

/*
* Ia input-ul utilizatorului si sterge materia din lista
*/
void ui_stergere(repo_materii* repo);

/*
* Afiseaza pe ecran lista de materii prime
*/
void ui_afisare(repo_materii* repo);

/*
* Ia input-ul utilizatorului si filtreaza lista de materii care incep cu litera introdusa
*/
void ui_filter_litera(repo_materii* repo);

/*
* Ia input-ul utilizatorului si filtreaza lista de materii care au cantitatea mai mica decat numarul introdus
*/
void ui_filter_cantitate(repo_materii* repo);

/*
* Sorteaza lista de materii in functie de criteriu si ordine
*/
void ui_sort(repo_materii* repo, CompareFunction comparare, int ascending);

/*
* Afiseaza meniul cu optiunile disponibile pt utilizator
*/
void meniu();

/*
* Porneste interfata utilizatorului
*/
void start_ui();

#endif