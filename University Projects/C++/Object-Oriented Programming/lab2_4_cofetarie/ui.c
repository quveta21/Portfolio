#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <stdio.h>
#include <string.h>

int int_valid(int* nr)
{
    char buffer[100], extra;
    if (fgets(buffer, sizeof(buffer), stdin))
        if (sscanf_s(buffer, "%d %c", nr, &extra, 1) == 1)
            return 1;
    return 0;
}

int input(char nume[50], char producator[50], int* cantitate)
{
    printf("Nume: ");
    fgets(nume, 50, stdin);
    nume[strcspn(nume, "\n")] = '\0';
    printf("Producator: ");
    fgets(producator, 50, stdin);
    producator[strcspn(producator, "\n")] = '\0';
    printf("Cantitate: ");
    if (!int_valid(cantitate))
    {
        printf("Valoarea introdusa nu este valida!\n");
        return 0;
    }
    return 1;
}

void ui_adaugare(repo_materii* repo) {
    char nume[50], producator[50];
    int cantitate;
    printf("Introduceti detaliile materiei prime:\n");
    input(nume, producator, &cantitate);
    switch (adaugare_materie(repo, nume, producator, cantitate)) {
    case 1:
        printf("Materia a fost adaugata cu succes!\n");
        break;
    case 0:
        printf("Eroare la repository!\n");
        break;
    case -1:
        printf("Nu ati introdus un nume valid!\n");
        break;
    case -2:
        printf("Nu ati introdus un producator valid!\n");
        break;
    case -3:
        printf("Nu ati introdus o cantitate valida!\n");
        break;
    }
    
}

void ui_stergere(repo_materii* repo) {
    char nume[50], producator[50];
    int cantitate;
    if (!input(nume, producator, &cantitate))
        return;
    if(!stergere_materie(repo, nume, producator))
        printf("Materia nu exista!\n");
    else
        printf("Materia a fost stearsa cu succes!\n");
}

void ui_modificare(repo_materii* repo) {
    char nume[50], producator[50], nume_nou[50], producator_nou[50];
    int cantitate, cantitate_noua;
    printf("Introduceti detaliile materiei prime:\n");
    if (!input(nume, producator, &cantitate))
        return;
    printf("\nIntroduceti detaliile pentru modificarea materiei prime:\n");
    if (!input(nume_nou, producator_nou, &cantitate_noua))
        return;
    if (!modificare_materie(repo, nume, producator, nume_nou, producator_nou, cantitate_noua))
        printf("Materia nu a fost gasita!\n");
    else
        printf("Materia a fost modificata cu succes!\n");
}

void ui_afisare(repo_materii* repo) {
    materie* lista_materii = toate_materiile(repo);
    if (repo->nr_materii > 0) {
        for (int i = 0; i < repo->nr_materii; i++) {
            printf("Nume: %s, Producator: %s, Cantitate: %d\n",
                lista_materii[i].nume, lista_materii[i].producator, lista_materii[i].cantitate);
        }
    }
    else
        printf("Nu exista materii!\n");
    
}

void ui_filter_litera(repo_materii* repo) {
    char litera;
    char buffer[100], extra;
    printf("Introduceti litera: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf_s(buffer, "%c %c", &litera, &extra, 1);
    materie lista_filtrata[MAX_MATERII];
    int nr = filtreaza_litera(repo, litera, lista_filtrata);
    if (nr > 0) {
        for (int i = 0; i < nr; i++) {
            printf("Nume: %s, Producator: %s, Cantitate: %d\n",
                lista_filtrata[i].nume, lista_filtrata[i].producator, lista_filtrata[i].cantitate);
        }
    }
    else
        printf("Nu exista materii care sa inceapa cu litera %c!\n", litera);
}

void ui_filter_cantitate(repo_materii* repo) {
    int cantitate;
    printf("Introduceti cantitatea: ");
    if (!int_valid(&cantitate)) {
        printf("Nu ati introdus o cantitate valida!\n");
        return;
    }
    materie lista_filtrata[MAX_MATERII];
    int nr = filtreaza_cantitate(repo, cantitate, lista_filtrata);
    if (nr > 0) {
        for (int i = 0; i < nr; i++) {
            printf("Nume: %s, Producator: %s, Cantitate: %d\n",
                lista_filtrata[i].nume, lista_filtrata[i].producator, lista_filtrata[i].cantitate);
        }
    }
    else
        printf("Nu exista materii cu cantitatea mai mica decat %d!\n", cantitate);
}

void ui_sort_nume(repo_materii* repo, materie* lista_sortata) {
    sorteaza_nume(repo, lista_sortata);
    if (repo->nr_materii > 0)
    {
        for (int i = 0; i < repo->nr_materii; i++) {
            printf("Nume: %s, Producator: %s, Cantitate: %d\n",
                lista_sortata[i].nume, lista_sortata[i].producator, lista_sortata[i].cantitate);
        }
    }
    else
        printf("Nu exista materii!\n");
}

void ui_sort_cantitate(repo_materii* repo, materie* lista_sortata) {
    sorteaza_cantitate(repo, lista_sortata);
    if (repo->nr_materii > 0)
    {
        for (int i = 0; i < repo->nr_materii; i++) {
            printf("Nume: %s, Producator: %s, Cantitate: %d\n",
                lista_sortata[i].nume, lista_sortata[i].producator, lista_sortata[i].cantitate);
        }
    }
    else
        printf("Nu exista materii!\n");
}

void meniu() {
    printf("1. Adauga materie prima\n");
    printf("2. Modifica materie prima\n");
    printf("3. Sterge materie prima\n");
    printf("4. Afiseaza materii prime\n");
    printf("5. Vizualizare materii care incep cu o litera data\n");
    printf("6. Vizualizare materii cu cantitatea < nr dat\n");
    printf("7. Vizualizare materii ordonate dupa nume/cantitate\n");
    printf("0. Iesire\n");
}

void start_ui() {
    repo_materii repo;
    init_repo(&repo);
    meniu();
    int run = 1;
    while (run) {
        int comanda = -1;
        printf("> ");
        if (!int_valid(&comanda)) {
            printf("Comanda invalida!\n");
            continue;
        }
        switch (comanda) {
        case 1: {
            ui_adaugare(&repo);
            break;
        }
        case 2: {
            ui_modificare(&repo);
            break;
        }
        case 3: {
            ui_stergere(&repo);
            break;
        }
        case 4:
            ui_afisare(&repo);
            break;
        case 5: {
            ui_filter_litera(&repo);
            break;
        }
        case 6: {
            ui_filter_cantitate(&repo);
            break;
        }
        case 7: {
            char optiune;
            materie lista_sortata[MAX_MATERII];
            printf("Alegeti sortare dupa nume sau cantitate (n/c): ");
            scanf(" %c", &optiune);
            if (optiune == 'n')
                ui_sort_nume(&repo, lista_sortata);
            else 
                if (optiune == 'c')
                    ui_sort_cantitate(&repo, lista_sortata);
                else
                    printf("Nu e o optiune valida! Introduceti n/c!\n");
            getchar();
            break;
        }
        case 0:
            run = 0;
            printf("La revedere!");
            break;
        default:
            printf("Comanda nu e valida!\n");
        }
            
    }
}