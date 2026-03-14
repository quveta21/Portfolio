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
	char nume[50], producator[50];
	int cantitate;
} materie;

/*
* Functie care creeaza o materie prima cu numele 'nume', producatorul 'producator' si cu cantitatea 'cantitate'
* :param nume: numele unic a materiei prime, string != ""
* :param producator: numele producatorului, string != ""
* :param cantitate: cantitatea de materie prima, int > 0
* :return: 0 (materia a fost creata cu succes)
*		   1 (nume invalid)
*		   2 (producator invalid)
*		   3 (cantitate invalida)
*/
materie creeaza(char nume[50], char producator[50], int cantitate);

#endif //MATERIE_H