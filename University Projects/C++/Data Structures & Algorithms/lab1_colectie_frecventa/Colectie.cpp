#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
	/* de adaugat */
	this->v = new TElem[10];
	this->size = 0;
	this->capacity = 10;
	this->minim = 100000;
	this->maxim = -100000;
}

//theta(n)
void Colectie::redimensioneaza(TElem* v) {
	this->capacity *= 2;
	TElem* new_v = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++) {
		new_v[i] = this->v[i];
	}
	delete[] this->v;
	this->v = new_v;
}

//best case - theta(1) (cand e intre minim si maxim si nu trebuie redimensionare)
//worst case - theta(n) (cand e inafara limitelor si trebuie redimensionare)
//complex totala o(n)
void Colectie::adauga(TElem elem) {
	/* de adaugat */
	if (this->size == 0) {
		this->minim = this->maxim = elem;
		this->v[0] = 1;
		this->size = 1;
		return;
	}
	if (elem < this->minim || elem > this->maxim) {
		TElem old_min = this->minim;
		TElem old_max = this->maxim;

		if (elem < this->minim) this->minim = elem;
		if (elem > this->maxim) this->maxim = elem;

		int new_size = this->maxim - this->minim + 1;
		while (new_size > this->capacity) {
			redimensioneaza(this->v);
		}
		TElem* new_v = new TElem[this->capacity](); //initializeaza elementele cu zero

		for (int i = 0; i < this->size; i++) {
			new_v[old_min - this->minim + i] = this->v[i];
		}
		delete[] this->v;
		this->v = new_v;
		this->size = new_size;
	}
	this->v[elem - this->minim]++;
}

//best case omega(1) - nu exista elem sau nu duce la redimensionare
//worst case o(n) - trebuie recalculat minim si maxim si realocat vectorul
bool Colectie::sterge(TElem elem) {
	/* de adaugat */
	if (elem < this->minim || elem > this->maxim || !cauta(elem)) {
		return false;
	}

	int old_min = this->minim;

	int index = elem - this->minim;
	this->v[index]--;

	if (this->v[index] == 0) {
		if (elem == this->minim) {
			for (int i = 0; i < this->size; i++) {
				if (this->v[i] > 0) {
					this->minim += i;
					break;
				}
			}
		}
		if (elem == this->maxim) {
			for (int i = this->size - 1; i >= 0; i--) {
				if (this->v[i] > 0) {
					this->maxim = this->minim + i;
					break;
				}
			}
		}

		if (minim > maxim) {
			minim = 100000;
			maxim = -100000;
			this->size = 0;
		}
		else {
			int old_size = this->size;
			this->size = this->maxim - this->minim + 1;
			if (this->size < old_size) {
				TElem* new_v = new TElem[this->size];
				for (int i = 0; i < this->size; i++) {
					new_v[i] = this->v[i + this->minim - old_min];
				}
				delete[] this->v;
				this->v = new_v;
				this->capacity = this->size;
			}
		}
	}
	return true;
}

//theta(1)
bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	if (this->minim <= elem && elem <= this->maxim) {
		if (this->nrAparitii(elem))
			return true;
	}
	return false;
}

//theta(1)
int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	if (this->minim <= elem && elem <= this->maxim)
		return this->v[elem - this->minim];
	return 0;
}

//theta(n)
int Colectie::dim() const {
	/* de adaugat */
	int nrElem = 0;
	for (int i = 0; i < this->size; i++) {
		nrElem += this->v[i];
	}
	return nrElem;
}

//theta(1)
bool Colectie::vida() const {
	/* de adaugat */
	return this->dim() == 0;
}

//theta(1) in caz ca nu apare
//theta(minim{aparitii,nr}) in caz ca apare
int Colectie::eliminaAparitii(int nr, TElem elem) {

	/*
	* Daca nr < 0 atunci
	*		@arunca exceptie
	* Sf. Daca
	* Daca cauta(elem) = false atunci
	*		@arunca exceptie
	* Sf. Daca
	* aparitii <- v[elem-minim]
	* rezultat <- min(aparitii, nr)
	* CatTimp aparitii != 0 si nr != 0 executa
	*		sterge(elem)
	*		aparitii <- aparitii - 1
	*		nr <- nr - 1
	* Sf. CatTimp
	* returneaza rezultat
	*/

	if (nr < 0)
		throw exception("Nr de aparitii nu poate fi negativ!\n");
	if (!cauta(elem))
		throw exception("Nu exista elementul!\n");
	int aparitii = v[elem - minim];
	int rezultat = min(aparitii, nr);
	while (aparitii && nr) {
		sterge(elem);
		aparitii--;
		nr--;
	}
	return rezultat;
}

//theta(1)
IteratorColectie Colectie::iterator() const {
	return IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
	delete[] this->v;
}


