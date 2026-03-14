#include "reteta.h"
#include <random>
#include <fstream>

Reteta::Reteta() noexcept {
	lista.clear();
}

void Reteta::addToReteta(const Medicament& m) {
	lista.push_back(m);
}

void Reteta::emptyReteta() noexcept {
	lista.clear();
}

void Reteta::generateReteta(const vector<Medicament>& elems, int n) {
	if (elems.empty())
		throw RetetaException("Nu putem adauga aleator dintr-o lista goala!\n");
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, (int)(elems.size()) - 1);
	for (int i = 0; i < n; i++) {
		const int rndNr = dist(mt);
		addToReteta(elems.at(rndNr));
	}
}

void Reteta::saveToFile(const string& filename) {
	if (lista.empty())
		throw RetetaException("Nu putem salva in fisier o reteta goala!\n");
	std::ofstream fout(filename);
	fout << "Ultima reteta salvata:\n";
	for (const auto& m : lista) {
		fout << "Denumire: " << m.getDenumire() << ", Pret: " << m.getPret()
			<< ", Producator: " << m.getProducator() << ", Substanta: " << m.getSubstanta() << '\n';
	}
}