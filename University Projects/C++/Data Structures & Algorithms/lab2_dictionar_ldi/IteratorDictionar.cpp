#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

//theta(1)
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d) {
	/* de adaugat */
	curent = dict.prim;
}

//theta(1)
void IteratorDictionar::prim() {
	/* de adaugat */
	curent = dict.prim;
}

//theta(1)
void IteratorDictionar::urmator() {
	/* de adaugat */
	if (valid())
		curent = curent->urm;
}

//theta(1)
TElem IteratorDictionar::element() const {
	/* de adaugat */
	if(!valid())
		return pair <TCheie, TValoare>(-1, -1);
	return curent->e;
}

//theta(1)
bool IteratorDictionar::valid() const {
	/* de adaugat */
	return curent != nullptr;
}

