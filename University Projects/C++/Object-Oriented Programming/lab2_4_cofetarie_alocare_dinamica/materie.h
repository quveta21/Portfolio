#ifndef MATERIE_H
#define MATERIE_H

#define MAX_MATERII 1000

//Interfata ce defineste o materie prima

/*
* Structura unei materii prime
* string nume - numele unic a materiei prime != ""
* string producator - numele producatorului != ""
* int cantitate - cantitatea de materie prima > 0
*/
typedef struct {
	char* nume;
	char* producator;
	int cantitate;
} materie;

/*
* Functie care creeaza o materie prima cu numele 'nume', producatorul 'producator' si cu cantitatea 'cantitate'
* :param nume: numele unic a materiei prime, string != ""
* :param producator: numele producatorului, string != ""
* :param cantitate: cantitatea de materie prima, int > 0
*/
void creeaza(char* nume, char* producator, int cantitate, materie* mat);

/*
* Functie care elibereaza memoria ocupata de o materie prima
* :param materie: referinta catre materie
*/
void distruge(materie* mat);

/*
* Verifica daca doua materii prime sunt egale
*/
int are_equal(materie* m1, materie* m2);

#endif //MATERIE_H