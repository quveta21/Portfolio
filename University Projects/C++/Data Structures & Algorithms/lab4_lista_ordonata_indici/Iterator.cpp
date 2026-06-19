#include "Iterator.h"
#include "LO.h"
#include <exception>

//theta(1)
Iterator::Iterator(const LO& lo) : lista(lo) {
	/* de adaugat */
	curent = lista.prim;
}

//theta(1)
void Iterator::prim() {
	/* de adaugat */
	curent = lista.prim;
}

//theta(1)
void Iterator::urmator() {
	/* de adaugat */
	if (!valid())
		throw std::exception();
	curent = lista.urm[curent];
}

//theta(1)
bool Iterator::valid() const {
	/* de adaugat */
	return curent != NULL_TELEMENT;
}

//theta(1)
TElement Iterator::element() const {
	/* de adaugat */
	if (!valid())
		throw std::exception();
	return lista.e[curent];
}


