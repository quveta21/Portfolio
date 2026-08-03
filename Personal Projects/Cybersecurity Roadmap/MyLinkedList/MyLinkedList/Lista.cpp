
#include <exception>

#include "IteratorLP.h"
#include "Lista.h"

#include <iostream>

Lista::Lista() {
	first = nullptr;
	size = 0;
}

int Lista::dim() const {
	return size;
}


bool Lista::vida() const {
	return size == 0;
}

IteratorLP Lista::prim() const {
    return IteratorLP(*this);
}

TElem Lista::element(IteratorLP poz) const {
	if (!poz.valid())
		throw std::exception();
	return poz.element();
}

TElem Lista::sterge(IteratorLP& poz) {
	if (!poz.valid())
		throw std::exception();
	
	Nod* nodDeSters;
	
	// tratam cazul primului element
	if (poz.curent == first)
	{
		nodDeSters = first;
		first = poz.curent->next;
	}
	else
	{
		Nod* curent = first;
	
		while (curent->next != poz.curent)
		{
			curent = curent->next;	
		}
		nodDeSters = curent->next;
		curent->next = poz.curent->next;
	}
	
	poz.urmator();	// mutam iteratorul 
	size--;
	
	TElem val = nodDeSters->e;
	delete nodDeSters;
	return val;
}

IteratorLP Lista::cauta(TElem e) const{
	IteratorLP it = this->prim();
	while (it.valid())
	{
		if (it.element() == e)
			break;
		it.urmator();
	}
	return it;
}

TElem Lista::modifica(IteratorLP poz, TElem e) {
	if (!poz.valid())
		throw std::exception();
	
	TElem valVeche = poz.element();
	poz.curent->e = e;
	
	return valVeche;
}

void Lista::adauga(IteratorLP& poz, TElem e) {
	if (!poz.valid())
		throw std::exception();
	
	Nod* nodNou = new Nod(e, poz.curent->next);
	poz.curent->next = nodNou;
	size++;
	poz.urmator();
}

void Lista::adaugaInceput(TElem e) {
	Nod* nodNou = new Nod(e, first);
	first = nodNou;
	size++;
}

void Lista::adaugaSfarsit(TElem e) {
	Nod* curent = first;
	Nod* nodNou = new Nod(e, nullptr);
	
	// TRATAM CAZUL LISTA VIDA!
	if (curent == nullptr)
	{
		first = nodNou;
	}
	else
	{
		while (curent->next != nullptr)
		{
			curent = curent->next;	
		}
		curent->next = nodNou;
	}
	
	size++;
}

Lista::~Lista() {
	Nod* curent = first;
	while (curent != nullptr)
	{
		Nod* nodDeSters = curent;
		curent = curent->next;
		delete nodDeSters;
	}
}
