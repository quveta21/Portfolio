#pragma once
#include <cstddef>

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
	TElem minim, maxim;
	TElem* v;
	int size;
	int capacity;

	//dubleaza capacitatea vectorului de frecvente cand depaseste dimensiunea alocata
	void redimensioneaza(TElem* v);
public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;


		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//elimina nr aparitii ale elementului elem
		int eliminaAparitii(int nr, TElem elem);

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// destructorul colectiei
		~Colectie();

};

