#pragma once

#include "repository.h"
#include "undo.h"
#include <memory>

typedef bool (*CompareFunction)(const Medicament& m1, const Medicament& m2);

/*
* Compara doua medicamente lexicografic dupa denumire, returneaza true
* daca primul medicament este "mai mare", false altfel
*/
bool compare_denumire(const Medicament& m1, const Medicament& m2);

/*
* Compara doua medicamente lexicografic dupa producator, returneaza true
* daca primul medicament este "mai mare", false altfel
*/
bool compare_producator(const Medicament& m1, const Medicament& m2);

/*
* Compara doua medicamente lexicografic dupa substanta activa + pret, returneaza true
* daca primul medicament este "mai mare", false altfel
*/
bool compare_subst_pret(const Medicament& m1, const Medicament& m2);

/*
* Clasa care gestioneaza service-ul aplicatiei
*/
class MedList {
private:
	MedicamentRepo& repo;
	vector<std::unique_ptr<ActiuneUndo>> undoAct;
public:
	/*
	* Constructorul service-ului care foloseste repository-ul
	*/
	MedList(MedicamentRepo& rep) noexcept : repo { rep } {

	}

	/*
	* Constructorul de copiere sterge obiectele copiate
	* (nu permite copierea acestora)
	*/
	MedList(const MedList& ot) = delete;

	MedList() = default;

	/*
	* Valideaza argumentele primite si adauga un medicament cu datele respective
	* in lista de medicamente
	*/
	void add(const string& denumire, int pret, const string& producator, const string& substanta);

	/*
	* Sterge al poz-lea medicament
	*/
	void rmv(int poz);

	/*
	* Modifica medicamentul de pe pozitia poz
	*/
	void modify(int poz, const string& denumire, int pret, const string& producator, const string& substanta);

	/*
	* Cauta medicamentul dupa denumire si producator
	*/
	const Medicament& search(const string& denumire, const string& producator);

	/*
	* Filtreaza medicamentele dupa pret
	*/
	vector<Medicament> filter_pret(int pret);

	/*
	* Filtreaza medicamentele dupa substanta activa
	*/
	vector<Medicament> filter_subst(const string& substanta);

	/*
	* Sorteaza medicamentele dupa criteriul cerut
	*/
	vector<Medicament> sort(CompareFunction compare);

	/*
	* Returneaza toate medicamentele din lista de medicamente
	*/
	const vector<Medicament>& getAll() noexcept {
		return repo.getAll();
	}

	/*
	* Face undo la ultima operatie efectuata, arunca exceptie daca nu exista operatii de facut undo
	*/
	void undo();
};