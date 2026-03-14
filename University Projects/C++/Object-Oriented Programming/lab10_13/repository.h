#pragma once

#include "domain.h"
#include <vector>
#include <map>
using std::vector;
using std::map;

/*
* Clasa pentru exceptiile din repository
*/
class RepoException {
	string msg;
public:
	RepoException(string m) : msg{ m } {
	}
	/*
	* Returneaza mesajul exceptiei - string
	*/
	string getMessage() {
		return msg;
	}

	~RepoException() = default;
};

/*
* Clasa care se ocupa de gestionarea listei de medicamente
*/
class MedicamentRepo {
private:
	vector<Medicament> lista;
	//VectDinNewDeleteT<Medicament> lista;
public:

	/*
	* Constructorul implicit al repository-ului
	*/
	MedicamentRepo() = default;

	/*
	* Constructorul de copiere distruge obiectele copiate
	* (nu permite copierea acestora)
	*/
	MedicamentRepo(const MedicamentRepo& ot) = delete;

	/*
	* Adauga un medicament in lista de medicamente, arunca RepoException
	* daca nu s-a putut face adaugarea
	*/
	virtual void store(const Medicament& medicament);

	/*
	* Sterge un medicament din lista de medicamente, arunca RepoException
	* daca pozitia nu este valida
	*/
	virtual void remove(int pozitie);

	/*
	* Inlocuieste medicamentul de pe pozitia poz cu un nou medicament
	* cu datele modificate
	*/
	virtual void replace(int poz, const Medicament& medicament_modificat);

	/*
	* Cauta medicamentul dupa denumire si producator
	* returneaza medicamentul daca il gaseste, arunca RepoException
	* daca nu il gaseste
	*/
	const Medicament& find(const string& denumire, const string& producator);

	/*
	* Insereaza medicamentul in lista pe pozitia transmisa ca argument
	*/
	virtual void insertAt(const Medicament& m, int poz);

	/*
	* Returneaza lista cu toate medicamentele
	*/
	virtual const vector<Medicament>& getAll() noexcept {
		return lista;
	}

	/*
	* Destructorul implicit al repository-ului
	*/
	virtual ~MedicamentRepo() = default;
};

class MedicamentRepoFile : public MedicamentRepo {
private:
	string filename;
	void loadFromFile();
	void writeToFile();
public:
	MedicamentRepoFile(string filename) : MedicamentRepo(), filename{ filename } {
		loadFromFile();
	}

	void store(const Medicament& medicament) override {
		MedicamentRepo::store(medicament);
		writeToFile();
	}

	void remove(int pozitie) override {
		MedicamentRepo::remove(pozitie);
		writeToFile();
	}

	void replace(int poz, const Medicament& medicament_modificat) override {
		MedicamentRepo::replace(poz, medicament_modificat);
		writeToFile();
	}

	void insertAt(const Medicament& m, int poz) override {
		MedicamentRepo::insertAt(m, poz);
		writeToFile();
	}
};
