#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* de adaugat */
	this->curent = 0;
	this->aparitii_curent = this->col.v[this->curent];
}

//theta(1)
void IteratorColectie::prim() {
	/* de adaugat */
	this->curent = 0;
	this->aparitii_curent = this->col.v[this->curent];
}

//best case omega(1) - aparitii_curent > 1
//worst case o(n) - urmator e chiar ultimul element
void IteratorColectie::urmator() {
	/* de adaugat */
	if (!valid())
		return;
	this->aparitii_curent--;
	if (this->aparitii_curent == 0) {
		this->curent++;
		while (this->valid() && !this->col.v[this->curent])
			this->curent++;
		if(this->valid())
			this->aparitii_curent = this->col.v[this->curent];
	}
}

//theta(1)
bool IteratorColectie::valid() const {
	/* de adaugat */
	if (curent < col.size)
		return true;
	return false;
}


//theta(1)
TElem IteratorColectie::element() const {
	/* de adaugat */
	if (!this->valid())
		return -100001;
	return this->col.minim + this->curent;
}
