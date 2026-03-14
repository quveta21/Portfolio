#include "domain.h"

string Medicament::getDenumire() const {
	return denumire;
}
int Medicament::getPret() const noexcept {
	return pret;
}
string Medicament::getProducator() const {
	return producator;
}
string Medicament::getSubstanta() const {
	return substanta;
}