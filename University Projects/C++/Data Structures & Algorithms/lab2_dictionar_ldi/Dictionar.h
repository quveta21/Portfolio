#pragma once


#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Nod {
private:
	TElem e;
	Nod* prec;
	Nod* urm;
public:
	friend class Dictionar;
	friend class IteratorDictionar;
	Nod(TElem e, Nod* prec, Nod* urm) : e{ e }, prec{ prec }, urm{ urm } {}
};

class Dictionar {
	friend class IteratorDictionar;

private:
	/* aici e reprezentarea */
	Nod* prim;
	Nod* ultim;

public:

	// constructorul implicit al dictionarului
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	int dim() const;

	//verifica daca dictionarul e vid 
	bool vid() const;

	/*adauga in dictionarul curent toate perechile din d a caror cheie
	nu se afla deja in dictionar*/
	int adaugaInexistente(Dictionar& d);

	// se returneaza iterator pe dictionar
	IteratorDictionar iterator() const;


	// destructorul dictionarului	
	~Dictionar();

};


