#include "service.h"
#include <algorithm>
#include <iterator>

void MedList::add(const string& denumire, int pret, const string& producator, const string& substanta) {
	//validare date
	Medicament m{ denumire, pret, producator, substanta };
	repo.store(m);
	undoAct.push_back(std::make_unique<UndoAdauga>(repo));
}

void MedList::rmv(int poz) {
	if (poz - 1 < 0 || poz - 1 >= repo.getAll().size())
		throw RepoException("Pozitia nu este valida...\n");
	const Medicament& m = repo.getAll().at(poz - 1);
	undoAct.push_back(std::make_unique<UndoSterge>(repo, m, poz - 1));
	repo.remove(poz);
}

void MedList::modify(int poz, const string& denumire, int pret, const string& producator, const string& substanta) {
	if (poz - 1 < 0 || poz - 1 >= repo.getAll().size())
		throw RepoException("Pozitia nu este valida...\n");
	Medicament m{ denumire, pret, producator, substanta };
	const Medicament& med = repo.getAll().at(poz - 1);
	undoAct.push_back(std::make_unique<UndoModifica>(repo, med, poz));
	repo.replace(poz, m); //pp ca introduce al catelea element, nu indicele
}

const Medicament& MedList::search(const string& denumire, const string& producator) {
	return repo.find(denumire, producator);
}

vector<Medicament> MedList::filter_pret(int pret) {
	vector<Medicament> lista_filtrata;
	auto lista = repo.getAll();
	/*for (const Medicament& m : lista) {
		if (m.getPret() <= pret)
			lista_filtrata.push_back(m);
	}*/

	std::copy_if(lista.begin(), lista.end(), std::back_inserter(lista_filtrata), [=](const Medicament& m) {return m.getPret() <= pret; });

	if (lista_filtrata.size() == 0)
		throw RepoException("Nu exista medicamente la pret mai mic...\n");
	return lista_filtrata;
}

vector<Medicament> MedList::filter_subst(const string& substanta) {
	vector<Medicament> lista_filtrata;
	auto lista = repo.getAll();
	/*for (const Medicament& m : lista) {
		if (m.getSubstanta() == substanta)
			lista_filtrata.push_back(m);
	}*/

	std::copy_if(lista.begin(), lista.end(), std::back_inserter(lista_filtrata), [=](const Medicament& m) {return m.getSubstanta() == substanta; });

	if (lista_filtrata.size() == 0)
		throw RepoException("Nu exista medicamente cu substanta ceruta...\n");
	return lista_filtrata;
}

bool compare_denumire(const Medicament& m1, const Medicament& m2) {
	return m1.getDenumire() < m2.getDenumire();
}

bool compare_producator(const Medicament& m1, const Medicament& m2) {
	return m1.getProducator() < m2.getProducator();
}

bool compare_subst_pret(const Medicament& m1, const Medicament& m2) {
	if (m1.getSubstanta() == m2.getSubstanta()) {
		return m1.getPret() < m2.getPret();
	}
	return m1.getSubstanta() < m2.getSubstanta();
}

vector<Medicament> MedList::sort(CompareFunction compare) {
	if (repo.getAll().size() == 0)
		throw RepoException("Nu exista medicamente de sortat...\n");
	vector<Medicament> lista_sortata = repo.getAll();
	/*int sorted = 0;
	while (!sorted) {
		sorted = 1;
		for (int i = 0; i < lista_sortata.size() - 1; i++) {
			if (compare(lista_sortata.at(i), lista_sortata.at(i + 1)) == 1) {
				std::swap(lista_sortata.at(i), lista_sortata.at(i + 1));
				sorted = 0;
			}
		}
	}*/
	std::sort(lista_sortata.begin(), lista_sortata.end(), compare);
	return lista_sortata;
}

void MedList::undo() {
	if (undoAct.empty())
		throw RepoException("Nu se poate face undo!\n");
	undoAct.back()->doUndo();
	undoAct.pop_back();
}
