#include "TestScurt.h"
#include <assert.h>
#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <cstring>




void testAll() { //apelam fiecare functie sa vedem daca exista
	Colectie c;
	assert(c.vida() == true);
	assert(c.dim() == 0); //adaug niste elemente
	c.adauga(5);
	c.adauga(1);
	c.adauga(10);
	c.adauga(7);
	c.adauga(1);
	c.adauga(11);
	c.adauga(-3);
	assert(c.dim() == 7);
	assert(c.cauta(10) == true);
	assert(c.cauta(16) == false);
	assert(c.nrAparitii(1) == 2);
	assert(c.nrAparitii(7) == 1);
	assert(c.sterge(1) == true);
	assert(c.sterge(6) == false);
	assert(c.dim() == 6);
	assert(c.nrAparitii(1) == 1);
	IteratorColectie ic = c.iterator();
	ic.prim();
	while (ic.valid()) {
		TElem e = ic.element();
		ic.urmator();
	}	 
}

void test_eliminaAparitii() {
	Colectie c;
	for (int i = 0; i < 10; i++) {
		c.adauga(i);
		c.adauga(i);
		c.adauga(i);
	}
	assert(c.dim() == 30);
	assert(c.cauta(0) == true);
	assert(c.eliminaAparitii(8, 0) == 3);
	assert(c.cauta(0) == false);
	assert(c.dim() == 27);
	assert(c.cauta(9) == true);
	assert(c.eliminaAparitii(5, 9) == 3);
	assert(c.cauta(9) == false);
	assert(c.dim() == 24);
	assert(c.eliminaAparitii(2, 4) == 2);
	assert(c.nrAparitii(4) == 1);
	for (int i = 1; i < 9; i++)
		c.eliminaAparitii(3, i);
	try {
		c.eliminaAparitii(2, 4);
		assert(false);
	}
	catch (std::exception& e) {
		assert(strcmp(e.what(), "Nu exista elementul!\n") == 0);
	}
	try {
		c.eliminaAparitii(-1, 4);
		assert(false);
	}
	catch (std::exception& e) {
		assert(strcmp(e.what(), "Nr de aparitii nu poate fi negativ!\n") == 0);
	}
}