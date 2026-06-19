#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

//theta(1)
Dictionar::Dictionar() {
	/* de adaugat */
	prim = nullptr;
	ultim = nullptr;
}

//theta(n)
Dictionar::~Dictionar() {
	/* de adaugat */
	Nod* curent = prim;
	while (curent != nullptr) {
		Nod* urm = curent->urm;
		delete curent;
		curent = urm;
	}
	prim = nullptr;
	ultim = nullptr;
}

//best case omega(1) - gaseste cheia la inceput si actualizeaza valoarea
//worst case o(n) - trece prin toate elementele pentru a gasi cheia
//					si adauga perechea la final
TValoare Dictionar::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	Nod* curent = prim;
	while (curent != nullptr) {
		if (curent->e.first == c) {
			TValoare veche = curent->e.second;
			curent->e.second = v;
			return veche;
		}
		curent = curent->urm;
	}

	Nod* nodNou = new Nod({ c, v }, ultim, nullptr);
	if (ultim != nullptr) {
		ultim->urm = nodNou;
	}
	else {
		prim = nodNou;
	}
	ultim = nodNou;
	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
//best case omega(1) - gaseste cheia la inceput
//worst case o(n) - nu gaseste cheia
TValoare Dictionar::cauta(TCheie c) const {
	/* de adaugat */
	Nod* curent = prim;
	while (curent != nullptr) {
		if (curent->e.first == c)
			return curent->e.second;
		curent = curent->urm;
	}
	return NULL_TVALOARE;
}

//best case omega(1) - gaseste cheia la inceput
//worst case o(n) - nu gaseste cheia
TValoare Dictionar::sterge(TCheie c) {
	/* de adaugat */
	Nod* curent = prim;
	while (curent != nullptr) {
		if (curent->e.first == c) {
			TValoare val = curent->e.second;

			if (curent->prec != nullptr)
				curent->prec->urm = curent->urm;
			else
				prim = curent->urm;

			if (curent->urm != nullptr)
				curent->urm->prec = curent->prec;
			else
				ultim = curent->prec;

			delete curent;
			return val;
		}
		curent = curent->urm;
	}
	return NULL_TVALOARE;
}

//theta(n)
int Dictionar::dim() const {
	/* de adaugat */
	int count = 0;
    Nod* curent = prim;
    while (curent != nullptr) {
        count++;
        curent = curent->urm;
    }
    return count;
}

//theta(1)
bool Dictionar::vid() const {
	/* de adaugat */
	return prim == nullptr && ultim == nullptr;
}

//theta(1)
IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}

//best case omega(n) - gaseste la inceput cheia dar tot parcurge tot dictionarul d
//worst case o(n*m) - daca cauta cheia pana la final
int Dictionar::adaugaInexistente(Dictionar& d) {

	/*
	* curent <- d.prim
	* nr <- 0
	* CatTimp curent != nullptr executa
	*		Daca cauta(curent->e.first) == NULL_TVALOARE atunci
	*				nodNou <- Nod({ curent->e.first , curent->e.second }, ultim, nullptr)
	*				Daca ultim != nullptr atunci
	*						ultim->urm <- nodNou
	*				Altfel
	*						prim <- nodNou
	*				Sf. Daca
	*				ultim <- nodNou
	*				nr <- nr + 1
	*		Sf. Daca
	*		curent <- curent->urm
	* Sf. CatTimp
	* returneaza nr
	*/

	Nod* curent = d.prim;
	int nr = 0;
	while (curent != nullptr) {
		if (cauta(curent->e.first) == NULL_TVALOARE) {
			//adauga(curent->e.first, curent->e.second);
			Nod* nodNou = new Nod({ curent->e.first , curent->e.second }, ultim, nullptr);
			if (ultim != nullptr) {
				ultim->urm = nodNou;
			}
			else {
				prim = nodNou;
			}
			ultim = nodNou;
			nr++;
		}
		curent = curent->urm;
	}
	return nr;
}
