#pragma once

#include <string>
using std::string;

//const - nu modifica starea obiectului
//const & - variabile/parametrii care nu sunt modificati

/*
* Clasa care se ocupa de gestionarea unui medicament
*/
class Medicament {
private:
	string denumire;
	int pret;
	string producator;
	string substanta;
public:
	string getDenumire() const;
	int getPret() const noexcept;
	string getProducator() const;
	string getSubstanta() const;

	/*
	* Constructorul medicamentului
	*/
	Medicament(string denumire, int pret, string producator, string substanta) :denumire{ denumire }, pret{ pret }, producator{ producator }, substanta{ substanta } {

	}

	Medicament() = default;

	/*
	* Constructorul de copiere al medicamentului
	*/
	/*Medicament(const Medicament& ot) : denumire{ ot.denumire }, pret{ ot.pret }, producator{ ot.producator }, substanta{ ot.substanta } {

	}
	*/
	/*Medicament(const Medicament&) = default;
	Medicament& operator=(const Medicament&) = default;*/
};
