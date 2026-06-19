#include "IteratorMDO.h"
#include "MDO.h"

void IteratorMDO::adaugaInStivaPanaLaMinim(int nod) {
	while (nod != -1) {
		s.push(nod);
		nod = dict.stang[nod];
	}
}

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	/* de adaugat */
	prim();
}

void IteratorMDO::prim() {
	/* de adaugat */
	while (!s.empty()) {
		s.pop();
	}
	curent = -1; // Initializam curent cu -1 (invalid)

	// incepem parcurgerea in-order din radacina
	adaugaInStivaPanaLaMinim(dict.radacina);

	// daca stiva nu este goala, primul element este in varful stivei
	if (!s.empty()) {
		curent = s.top();
	}
}

void IteratorMDO::urmator() {
	/* de adaugat */
	if (!valid()) {
		throw std::exception("Iterator invalid!");
	}

	// scoatem nodul curent din stiva
	s.pop();

	// daca exista un subarbore drept, adaugam toate nodurile din subarborele stang al acestuia in stiva
	if (dict.drept[curent] != -1) {
		adaugaInStivaPanaLaMinim(dict.drept[curent]);
	}

	// urmatorul element este in varful stivei (daca mai exista)
	if (!s.empty()) {
		curent = s.top();
	}
	else {
		curent = -1; // nu mai sunt elemente de parcurs
	}
}

bool IteratorMDO::valid() const {
	/* de adaugat */
	return curent != -1;
}

TElem IteratorMDO::element() const {
	/* de adaugat */
	if(!valid())
		return pair <TCheie, TValoare>(-1, -1);
	return dict.elemente[curent];
}


