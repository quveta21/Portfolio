#define _CRT_SECURE_NO_WARNINGS
#include "materie.h"
#include <string.h>



materie creeaza(char nume[50], char producator[50], int cantitate) {
	materie m;
	strcpy(m.nume, nume);
	strcpy(m.producator, producator);
	m.cantitate = cantitate;
	return m;
}