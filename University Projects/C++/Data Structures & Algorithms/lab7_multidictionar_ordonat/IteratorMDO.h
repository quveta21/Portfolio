#pragma once

#include "MDO.h"
#include <stack>


class IteratorMDO {
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;
	/* aici e reprezentarea  specifica a iteratorului */
	std::stack<int> s; // stiva pentru a stoca indicii nodurilor in timpul parcurgerii in-order
	int curent;

	// functie ajutatoare pentru a adauga toate nodurile din subarborele stang in stiva
	void adaugaInStivaPanaLaMinim(int nod);

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;
};

