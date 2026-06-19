#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
private:
	/* aici e reprezentarea */

	Relatie rel;
	TElem* elemente;
	int* stang;
	int* drept;
	int capacitate;
	int radacina;
	int primLiber;
	int dimensiune;

	void redim();
	int alocaNod(TCheie c, TValoare v);
	void elibereazaNod(int poz);
	int stergeRecursiv(int nod, TCheie c, TValoare v, bool& gasit);
	int minim(int nod) const;
	int maxim(int nod) const;

public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	//returneaza diferenta dintre cheia maxima si cheia minima (presupunem valori intregi)
	int diferentaCheieMaxMin() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

};
