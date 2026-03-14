#pragma once

#include <vector>
#include "domain.h"

using std::vector;

class RetetaException {
	string msg;
public:
	RetetaException(string m) : msg{ m } {
	}
	/*
	* Returneaza mesajul exceptiei - string
	*/
	string getMessage() {
		return msg;
	}

	~RetetaException() = default;
};

class Reteta {
private:
	vector<Medicament> lista;
public:
	/*
	* Constructorul retetei fara argumente
	*/
	Reteta() noexcept;

	/*
	* Returneaza toate medicamentele din reteta
	*/
	const vector<Medicament>& getAll() {
		if(lista.empty())
			throw RetetaException("Nu exista medicamente in reteta!\n");
		return lista;
	}

	/*
	* Adauga medicament in reteta
	*/
	void addToReteta(const Medicament& m);

	/*
	* Goleste lista de medicamente din reteta
	*/
	void emptyReteta() noexcept;

	/*
	* Populeaza lista cu n elemente aleatorii din lista de medicamente
	*/
	void generateReteta(const vector<Medicament>& elems, int n);

	/*
	* Salveaza reteta curenta in fisierul filename
	*/
	void saveToFile(const string& filename);
};