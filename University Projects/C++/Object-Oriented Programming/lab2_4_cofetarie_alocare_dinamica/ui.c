#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int int_valid(int* nr)
{
    char buffer[100], extra;
    if (fgets(buffer, sizeof(buffer), stdin))
        if (sscanf_s(buffer, "%d %c", nr, &extra, 1) == 1)
            return 1;
    return 0;
}

int input(char* nume, char* producator, int* cantitate)
{
    printf("Nume: ");
    fgets(nume, 100, stdin);
    nume[strcspn(nume, "\n")] = '\0';
    printf("Producator: ");
    fgets(producator, 100, stdin);
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
    char nume[100], producator[100];
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
    char nume[100], producator[100];
    int cantitate;
    if (!input(nume, producator, &cantitate))
        return;
    if (!stergere_materie(repo, nume, producator))
        printf("Materia nu exista!\n");
    else
        printf("Materia a fost stearsa cu succes!\n");
}

void ui_modificare(repo_materii* repo) {
    char nume[100], producator[100], nume_nou[100], producator_nou[100];
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
    sscanf_s(buffer, "%c %c", &litera, 1, &extra, 1);
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

void ui_sort(repo_materii* repo, CompareFunction comparare, int ascending) {
    materie* lista_sortata = sorteaza(repo, comparare, ascending);
    if (lista_sortata)
    {
        for (int i = 0; i < repo->nr_materii; i++) {
            printf("Nume: %s, Producator: %s, Cantitate: %d\n",
                lista_sortata[i].nume, lista_sortata[i].producator, lista_sortata[i].cantitate);
        }
    }
    else
        printf("Nu exista materii!\n");
    destroy_list(lista_sortata, repo->nr_materii);
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
            int ascending;
            printf("Alegeti 1 pentru sortarea crescatoare, 0 pentru descrescatoare: ");
            if (!int_valid(&ascending) || !(ascending == 0 || ascending == 1)) {
                printf("Optiune de sortare invalida!\n");
                break;
            }
            printf("Alegeti sortare dupa nume sau cantitate (n/c): ");
            if (scanf(" %c", &optiune) != 1) {
                printf("Eroare la citirea optiunii!\n");
                break;
            }
            if (optiune == 'n')
                ui_sort(&repo, compara_nume, ascending);
            else
                if (optiune == 'c')
                    ui_sort(&repo, compara_cantitate, ascending);
                else
                    printf("Nu e o optiune valida! Introduceti n/c!\n");
            while (getchar() != '\n');
            break;
        }
        case 0:
            distruge_repo(&repo);
            run = 0;
            printf("La revedere!");
            break;
        default:
            printf("Comanda nu e valida!\n");
        }

    }
}