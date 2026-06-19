#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

//0(1) fara redimensionare
//0(n) cu redimensionare
int MDO::alocaNod(TCheie c, TValoare v) {
	if (this->primLiber == -1) {
		this->redim();
	}
	int poz = this->primLiber;
	this->primLiber = this->stang[poz];
	this->elemente[poz] = make_pair(c, v);
	this->stang[poz] = -1;
	this->drept[poz] = -1;
	return poz;
}

//0(1)
void MDO::elibereazaNod(int poz) {
	this->stang[poz] = this->primLiber;
	this->primLiber = poz;
}

//0(1) caz favorabil
//0(n) caz defavorabil
int MDO::minim(int nod) const{
	int curent = nod;
	while (this->stang[curent] != -1) {
		curent = this->stang[curent];
	}
	return curent;
}

//0(1) caz favorabil
//0(n) caz defavorabil
int MDO::maxim(int nod) const{
	int curent = nod;
	while (curent != -1 && this->drept[curent] != -1) {
		curent = this->drept[curent];
	}
	return curent;
}

//0(1) caz favorabil
//0(n) caz defavorabil
int MDO::stergeRecursiv(int nod, TCheie c, TValoare v, bool& gasit) {
	if (nod == -1) {
		return -1;
	}

	if (this->elemente[nod].first == c && this->elemente[nod].second == v) {
		gasit = true;
		this->dimensiune--;
		// caz 1: nodul este frunza
		if (this->stang[nod] == -1 && this->drept[nod] == -1) {
			elibereazaNod(nod);
			return -1;
		}
		// caz 2 : nodul are un singur copil
		if (this->stang[nod] == -1) {
			int temp = this->drept[nod];
			elibereazaNod(nod);
			return temp;
		}
		if (this->drept[nod] == -1) {
			int temp = this->stang[nod];
			elibereazaNod(nod);
			return temp;
		}
		// caz 3: nodul are doi copii
		int succesor = minim(this->drept[nod]);
		this->elemente[nod] = this->elemente[succesor];
		bool succesorGasit = false;
		this->drept[nod] = stergeRecursiv(this->drept[nod], this->elemente[succesor].first, this->elemente[succesor].second, succesorGasit);
		// dimensiunea a fost deja decrementata, deci nu mai trebuie sa o facem in apelul recursiv
		this->dimensiune++;
	}
	else if (this->rel(c, this->elemente[nod].first)) {
		this->stang[nod] = stergeRecursiv(this->stang[nod], c, v, gasit);
	}
	else {
		this->drept[nod] = stergeRecursiv(this->drept[nod], c, v, gasit);
	}
	return nod;
}

//0(n)
void MDO::redim() {
	int nouaCapacitate = this->capacitate * 2;
	TElem* elementeNoi = new TElem[nouaCapacitate];
	int* stangNou = new int[nouaCapacitate];
	int* dreptNou = new int[nouaCapacitate];

	for (int i = 0; i < this->capacitate; ++i) {
		elementeNoi[i] = this->elemente[i];
		stangNou[i] = this->stang[i];
		dreptNou[i] = this->drept[i];
	}

	// Initializam noua lista de spatii libere
	for (int i = this->capacitate; i < nouaCapacitate - 1; ++i) {
		stangNou[i] = i + 1;
	}
	stangNou[nouaCapacitate - 1] = -1;
	this->primLiber = this->capacitate;

	delete[] this->elemente;
	delete[] this->stang;
	delete[] this->drept;

	this->elemente = elementeNoi;
	this->stang = stangNou;
	this->drept = dreptNou;
	this->capacitate = nouaCapacitate;
}

//0(n) - n este capacitatea
MDO::MDO(Relatie r) {
	/* de adaugat */
	this->rel = r;
	this->capacitate = 10;
	this->elemente = new TElem[this->capacitate];
	this->stang = new int[this->capacitate];
	this->drept = new int[this->capacitate];
	this->radacina = -1;
	this->dimensiune = 0;

	// initializam lista de spatii libere
	for (int i = 0; i < this->capacitate - 1; ++i) {
		this->stang[i] = i + 1;
	}
	this->stang[this->capacitate - 1] = -1;
	this->primLiber = 0;
}


//0(1) caz favorabil
//0(n) caz defavorabil
void MDO::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	if (this->radacina == -1) {
		this->radacina = alocaNod(c, v);
		this->dimensiune++;
		return;
	}

	int curent = this->radacina;
	int parinte = -1;

	while (curent != -1) {
		parinte = curent;
		if (this->rel(c, this->elemente[curent].first)) {
			curent = this->stang[curent];
		}
		else {
			curent = this->drept[curent];
		}
	}

	int nodNou = alocaNod(c, v);
	if (this->rel(c, this->elemente[parinte].first)) {
		this->stang[parinte] = nodNou;
	}
	else {
		this->drept[parinte] = nodNou;
	}
	this->dimensiune++;
}

//0(logn + k) - k e nr aparitiilor a cheii
//0(n + k) daca gasim si in stanga si in dreapta cheii

vector<TValoare> MDO::cauta(TCheie c) const {
	/* de adaugat */
	vector<TValoare> valori;
	int curent = this->radacina;
	while (curent != -1) {
		if (this->elemente[curent].first == c) {
			// am gasit cheia, acum cautam toate valorile
			int temp = curent;
			// cautam in subarborele stang dupa chei identice
			while (temp != -1 && this->elemente[temp].first == c) {
				valori.push_back(this->elemente[temp].second);
				temp = this->stang[temp];
			}
			// cautam in subarborele drept dupa chei identice
			temp = this->drept[curent];
			while (temp != -1) {
				if (this->elemente[temp].first == c) {
					valori.push_back(this->elemente[temp].second);
					// cheile egale pot fi doar in subarborele drept, conform adaugarii
					temp = this->drept[temp];
				}
				else if (this->rel(c, this->elemente[temp].first)) {
					temp = this->stang[temp];
				}
				else {
					temp = this->drept[temp];
				}
			}
			return valori;
		}
		if (this->rel(c, this->elemente[curent].first)) {
			curent = this->stang[curent];
		}
		else {
			curent = this->drept[curent];
		}
	}
	return valori;
}

//0(1) caz favorabil
//0(n) caz defavorabil
bool MDO::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	bool gasit = false;
	this->radacina = stergeRecursiv(this->radacina, c, v, gasit);
	return gasit;
}

//0(1)
int MDO::dim() const {
	/* de adaugat */
	return this->dimensiune;
}

//0(1)
bool MDO::vid() const {
	/* de adaugat */
	return this->dimensiune == 0;
}

//0(1)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	/* de adaugat */
	delete[] this->elemente;
	delete[] this->stang;
	delete[] this->drept;
}

//0(1) caz favorabil
//0(n*n) caz defavorabil cand nu gasim rapid minim si maxim
int MDO::diferentaCheieMaxMin() const {
	/*
	* Daca e vid
	*	diferentaCheieMaxMin <- -1
	* min = minim(radacina)
	* max = maxim(radacina)
	* diferentaCheieMaxMin <- max.cheie - min.cheie
	*/
	if (vid())
		return -1;
	int min = minim(this->radacina);
	int max = maxim(this->radacina);

	return elemente[max].first - elemente[min].first;
}
