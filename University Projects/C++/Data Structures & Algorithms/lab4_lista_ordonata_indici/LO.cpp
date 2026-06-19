#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

//best case 0(1) - nu redimensionam
//worst case 0(n) - redimensionam si stabilim legaturile intre elemente
int LO::aloca() {
	if (primLiber == NULL_TELEMENT)
		redimensioneaza();
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

//0(1)
void LO::dealoca(int i) {
	urm[i] = primLiber;
	primLiber = i;
}

//0(1) amortizat
void LO::redimensioneaza() {
	int cp_noua = cp * 2;
	e.resize(cp_noua, NULL_TELEMENT);
	urm.resize(cp_noua, NULL_TELEMENT);
	for (int i = cp; i < cp_noua - 1; i++) {
		urm[i] = i + 1;
	}
	urm[cp_noua - 1] = primLiber;
	primLiber = cp;
	cp = cp_noua;
}

//0(n) - n = cp
LO::LO(Relatie r) : rel{ r } {
	/* de adaugat */
	prim = NULL_TELEMENT;
	e.resize(cp, NULL_TELEMENT);
	urm.resize(cp, NULL_TELEMENT);
	for (int i = 0; i < cp - 1; i++) {
		urm[i] = i + 1;
	}
	urm[cp - 1] = NULL_TELEMENT;
	primLiber = 0;
}

//0(n)
// returnare dimensiune
int LO::dim() const {
	/* de adaugat */
	int cnt = 0;
	TPozitie p = prim;
	while (p != NULL_TELEMENT) {
		cnt++;
		p = urm[p];
	}
	return cnt;
}

//0(1)
// verifica daca LO e vida
bool LO::vida() const {
	/* de adaugat */
	return prim == NULL_TELEMENT;
}

//0(n) -> n = i
// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const {
	/* de adaugat */
	TPozitie p = prim;
	while (p != NULL_TELEMENT) {
		if (p == i)
			return e[i];
		p = urm[p];
	}
	throw exception();
}

//best case 0(1) daca e primul element
//worst case 0(n) daca e ultimul element
// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	/* de adaugat */
	if (i < 0 || i >= cp) {
		throw exception();
	}
	if (prim == i) {
		prim = urm[prim];
	}
	else {
		TPozitie p = prim;
		while (p != NULL_TELEMENT && urm[p] != i) {
			p = urm[p];
		}
		if (p == NULL_TELEMENT) {
			throw exception();
		}
		urm[p] = urm[i];
	}
	TElement val = e[i];
	dealoca(i);
	return val;
}

// best case - 0(1)
// worst case - 0(n)
// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	/* de adaugat */
	TPozitie p = prim;
	while (p != NULL_TELEMENT) {
		if (this->e[p] == e) {
			return p;
		}
		p = urm[p];
	}
	return -1;
}

//best case - 0(1) cand elem e adaugat la inceput
// worst case - 0(n) cand elem e adaugat la final
// adaugare element in LO
void LO::adauga(TElement e) {
	/* de adaugat */
	int pozNoua = aloca();
	this->e[pozNoua] = e;

	if (prim == NULL_TELEMENT || rel(e, this->e[prim])) {
		urm[pozNoua] = prim;
		prim = pozNoua;
	}
	else {
		TPozitie p = prim;
		while (urm[p] != NULL_TELEMENT && rel(this->e[urm[p]], e)) {
			p = urm[p];
		}
		urm[pozNoua] = urm[p];
		urm[p] = pozNoua;
	}
}

//theta(1)
// returnare iterator
Iterator LO::iterator() {
	return Iterator(*this);
}

//0(1)
//destructor
LO::~LO() = default;

//best case 0(1)
//worst case 0(n)
void LO::stergeIntre(TPozitie inceput, TPozitie sfarsit) {
	/*
	* Daca inceput < 0 sau sfarsit < inceput sau sfarsit >= dim()
	*		@arunca exceptie
	* Sf.Daca
	* p <- prim
	* deSters <- sfarsit - inceput + 1
	* CatTimp p != inceput executa:
	*		p <- urm[p]
	* Sf.CatTimp
	* CatTimp deSters > 0 si p != NULL_TELEMENT
	*		indiceNext <- urm[p]
	*		sterge(p)
	*		deSters <- deSters - 1
	*		p <- indiceNext
	* Sf.CatTimp
	*/
	if (inceput < 0 || sfarsit < inceput || sfarsit >= dim()) {
		throw exception();
	}
	TPozitie p = prim;
	int deSters = sfarsit - inceput + 1;
	while (p != inceput) {
		p = urm[p];
	}
	while (deSters && p != NULL_TELEMENT) {
		TPozitie indiceNext = urm[p];
		sterge(p);
		deSters--;
		p = indiceNext;
	}
}
