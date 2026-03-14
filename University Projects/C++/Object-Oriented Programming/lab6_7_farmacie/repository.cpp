#include "repository.h"
#include <fstream>
#include <sstream>
#include <random>

void MedicamentRepo::store(const Medicament& medicament) {
	/*for (auto it = lista.begin(); it != lista.end(); ++it) {
		const Medicament & m = *it;
		if (m.getDenumire() == medicament.getDenumire() && m.getProducator() == medicament.getProducator())
			throw RepoException("Medicamentul exista deja...\n"); }
	lista.add(medicament);*/
	for (const Medicament& m : lista) {
		if (m.getDenumire() == medicament.getDenumire() && m.getProducator() == medicament.getProducator())
			throw RepoException("Medicamentul exista deja...\n");
	}
	lista.push_back(medicament);
}

void MedicamentRepo::remove(int poz) {
	/*if (poz - 1 < 0 || poz - 1 >= lista.size())
		throw RepoException("Pozitia nu este valida...\n");*/
	lista.erase(lista.begin() + poz - 1);
}

void MedicamentRepo::replace(int poz, const Medicament& medicament_modificat) {
	/*if (poz - 1 < 0 || poz - 1 >= lista.size())
		throw RepoException("Pozitia nu este valida...\n");*/
	lista.at(poz - 1) = medicament_modificat;
	//lista.set(poz - 1, medicament_modificat);
}

const Medicament& MedicamentRepo::find(const string& denumire, const string& producator) {
	/*for (const Medicament& m : lista) {
		if (m.getDenumire() == denumire && m.getProducator() == producator)
			return m;
	}*/
	auto it = std::find_if(lista.begin(), lista.end(), [&](const Medicament& m) {
		return m.getDenumire() == denumire && m.getProducator() == producator;
	});
	if(it == lista.end())
		throw RepoException("Medicamentul nu a fost gasit...\n"); 
	return *it;
}

void MedicamentRepo::insertAt(const Medicament& m, int poz) {
	if (poz < 0 || poz > lista.size()) {
		throw RepoException("Pozitie invalida pentru inserare!\n");
	}
	lista.insert(lista.begin() + poz, m);
}

void MedicamentRepoFile::loadFromFile() {
	std::ifstream fin(filename);
	if (!fin.is_open())
		throw RepoException("Nu s-a putut deschide fisierul " + filename + "...\n");
	string linie;
	while (getline(fin, linie)) {
		std::stringstream ss(linie);
		string camp;
		vector<string> med;
		while (getline(ss, camp, ' ')) {
			med.push_back(camp);
		}
		int pret = 0;
		for (auto& ch : med.at(1))
			pret = pret * 10 + (ch - '0');
		const Medicament m{ med.at(0), pret, med.at(2), med.at(3) };
		MedicamentRepo::store(m);
	}
	fin.close();
}

void MedicamentRepoFile::writeToFile() {
	std::ofstream fout(filename);
	for (auto& m : MedicamentRepo::getAll()) {
		fout << m.getDenumire() << " " << m.getPret() << " " << m.getProducator() << " " << m.getSubstanta() << "\n";
	}
	fout.close();
}