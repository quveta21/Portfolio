#include "test.h"
#include "service.h"
#include "repository.h"
#include "reteta.h"
#include <iostream>

using std::cout;

void testRepoAll() {
	testDomain();
	testRepo();
	testRemove();
	testReplace();
	testFind();
	testVectDinT();
	testRepoFile();
}

void testServiceAll() {
	testAdd();
	testRmv();
	testModify();
	testSearch();
	testFilterPret();
	testFilterSubstanta();
	testSort();
	testUndo();
}

void testDomain() {
	Medicament m{ "Nurofen", 50, "Furdui", "Ibuprofen" };
	assert(m.getDenumire().compare("Nurofen") == 0);
	assert(m.getPret() == 50);
	assert(m.getProducator().compare("Furdui") == 0);
	assert(m.getSubstanta().compare("Ibuprofen") == 0);
}

void testRepo() {
	MedicamentRepo repo;
	Medicament m{ "Nurofen", 50, "Furdui", "Ibuprofen" };
	repo.store(m);
	const auto& medicamente = repo.getAll();
	assert(medicamente.size() == 1);
	try {
		repo.store(m); assert(false);
	}
	catch(RepoException & e){
		assert(e.getMessage().compare("Medicamentul exista deja...\n") == 0);
		assert(true);
	}
}

void testAdd() {
	MedicamentRepo repo;
	MedList service{ repo };
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	const auto& medicamente = service.getAll();
	assert(medicamente.size() == 1);
}

void testRemove() {
	MedicamentRepo repo;
	Medicament m{ "Nurofen", 50, "Furdui", "Ibuprofen" };
	repo.store(m);
	const auto& medicamente = repo.getAll();
	assert(medicamente.size() == 1);
	repo.remove(1);
	assert(medicamente.size() == 0);
	/*try {
		repo.remove(1);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().compare("Pozitia nu este valida...\n") == 0);
		assert(true);
	}*/
}

void testReplace() {
	MedicamentRepo repo;
	Medicament m{ "Nurofen", 50, "Furdui", "Ibuprofen" };
	repo.store(m);
	const auto& medicamente = repo.getAll();
	assert(medicamente.at(0).getDenumire().compare("Nurofen") == 0);
	Medicament m2{ "Theraflu", 30, "Alex", "Paracetamol" };
	repo.replace(1, m2);
	assert(medicamente.at(0).getDenumire().compare("Nurofen") != 0);
	assert(medicamente.at(0).getDenumire().compare("Theraflu") == 0);
}

void testRmv() {
	MedicamentRepo repo;
	MedList service{ repo };
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	const auto& medicamente = service.getAll();
	assert(medicamente.size() == 1);
	service.rmv(1);
	assert(medicamente.size() == 0);
	try {
		service.rmv(2); assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().compare("Pozitia nu este valida...\n") == 0);
	}
}

void testModify() {
	MedicamentRepo repo;
	MedList service{ repo };
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	const auto& medicamente = service.getAll();
	assert(medicamente.at(0).getDenumire().compare("Nurofen") == 0);
	service.modify(1, "Theraflu", 30, "Alex", "Paracetamol");
	assert(medicamente.at(0).getDenumire().compare("Nurofen") != 0);
	assert(medicamente.at(0).getDenumire().compare("Theraflu") == 0);
	try {
		service.modify(4, "Theraflu", 30, "Alex", "Paracetamol"); assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().compare("Pozitia nu este valida...\n") == 0);
	}
}

void testFind() {
	MedicamentRepo repo;
	Medicament m{ "Nurofen", 50, "Furdui", "Ibuprofen" };
	repo.store(m);
	const auto& med = repo.find("Nurofen", "Furdui");
	assert(med.getDenumire() == "Nurofen");
	try {
		repo.find("Theraflu", "Alex"); assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage() == "Medicamentul nu a fost gasit...\n");
	}
}

void testSearch() {
	MedicamentRepo repo;
	MedList service{ repo };
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	const auto& m = service.search("Nurofen", "Furdui");
	assert(m.getDenumire() == "Nurofen");
	try {
		service.search("Theraflu", "Alex"); assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage() == "Medicamentul nu a fost gasit...\n");
	}
}

void testFilterPret() {
	MedicamentRepo repo;
	MedList service{ repo };
	try {
		auto lista_filtrata = service.filter_pret(50); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Nu exista medicamente la pret mai mic...\n");
	}
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	service.add("Theraflu", 100, "Alex", "Paracetamol");
	service.add("Algocalmin", 150, "Marc", "Metamizol");
	auto lista_filtrata = service.filter_pret(75);
	assert(lista_filtrata.at(0).getDenumire() == "Nurofen");
}

void testFilterSubstanta() {
	MedicamentRepo repo;
	MedList service{ repo };
	try {
		auto lista_filtrata = service.filter_subst("Ibuprofen"); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage() == "Nu exista medicamente cu substanta ceruta...\n");
	}
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	service.add("Theraflu", 100, "Alex", "Paracetamol");
	service.add("Algocalmin", 150, "Marc", "Metamizol");
	auto lista_filtrata = service.filter_subst("Paracetamol");
	assert(lista_filtrata.at(0).getDenumire() == "Theraflu");
}

void testSort() {
	MedicamentRepo repo;
	MedList service{ repo };
	vector<Medicament> medicamente;
	try {
		medicamente = service.sort(compare_denumire); assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage() == "Nu exista medicamente de sortat...\n");
	}
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	service.add("Medicament1", 30, "Alex", "Ibuprofen");
	service.add("Theraflu", 70, "Marc", "Paracetamol");
	medicamente = service.sort(compare_denumire);
	assert(medicamente.at(0).getDenumire().compare("Medicament1") == 0);
	assert(medicamente.at(1).getDenumire().compare("Nurofen") == 0);
	assert(medicamente.at(2).getDenumire().compare("Theraflu") == 0);
	medicamente = service.sort(compare_producator);
	assert(medicamente.at(0).getProducator().compare("Alex") == 0);
	assert(medicamente.at(1).getProducator().compare("Furdui") == 0);
	assert(medicamente.at(2).getProducator().compare("Marc") == 0);
	service.add("Medicament2", 80, "Marc", "Amidon");
	medicamente = service.sort(compare_subst_pret);
	assert(medicamente.at(0).getDenumire().compare("Medicament2") == 0);
	assert(medicamente.at(1).getDenumire().compare("Medicament1") == 0);
	assert(medicamente.at(2).getDenumire().compare("Nurofen") == 0);
	assert(medicamente.at(3).getDenumire().compare("Theraflu") == 0);
}

void testVectDinT() {
	MedicamentRepo repo;
	Medicament m1{ "Nurofen1", 50, "Furdui1", "Ibuprofen1" };
	Medicament m2{ "Nurofen2", 50, "Furdui2", "Ibuprofen2" };
	Medicament m3{ "Nurofen3", 50, "Furdui3", "Ibuprofen3" };
	Medicament m4{ "Nurofen4", 50, "Furdui4", "Ibuprofen4" };
	Medicament m5{ "Nurofen5", 50, "Furdui5", "Ibuprofen5" };
	Medicament m6{ "Nurofen6", 50, "Furdui6", "Ibuprofen6" };
	repo.store(m1);
	repo.store(m2);
	repo.store(m3);
	repo.store(m4);
	repo.store(m5);
	repo.store(m6);
	repo.remove(3);
}

void testReteta() {
	Reteta reteta;
	MedicamentRepo repo;
	MedList service{ repo };
	try {
		reteta.getAll(); assert(false); }
	catch (RetetaException& e) {
		assert(e.getMessage().compare("Nu exista medicamente in reteta!\n") == 0);
	}
	Medicament m1{ "Nurofen", 50, "Furdui", "Ibuprofen" };
	Medicament m2{ "Medicament1", 30, "Alex", "Ibuprofen" };
	Medicament m3{ "Theraflu", 70, "Marc", "Paracetamol" };
	reteta.addToReteta(m1);
	reteta.addToReteta(m2);
	reteta.addToReteta(m3);
	assert(reteta.getAll().size() == 3);
	reteta.emptyReteta();
	try {
		reteta.getAll(); assert(false);
	}
	catch (RetetaException& e) {
		assert(e.getMessage().compare("Nu exista medicamente in reteta!\n") == 0);
	}
	try {
		reteta.generateReteta(service.getAll(), 5); assert(false);
	}
	catch(RetetaException& e){
		assert(e.getMessage().compare("Nu putem adauga aleator dintr-o lista goala!\n") == 0);
	}
	try {
		reteta.saveToFile("test.out"); assert(false);
	}
	catch (RetetaException& e) {
		assert(e.getMessage().compare("Nu putem salva in fisier o reteta goala!\n") == 0);
	}
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	service.add("Theraflu", 100, "Marc", "Paracetamol");
	service.add("Medicament1", 30, "Alex", "Ibuprofen");
	reteta.generateReteta(service.getAll(), 5);
	assert(reteta.getAll().size() == 5);
	reteta.saveToFile("test.out");
}

void testUndo() {
	MedicamentRepo repo;
	MedList service{ repo };
	try {
		service.undo(); assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().compare("Nu se poate face undo!\n") == 0);
	}
	service.add("Nurofen", 50, "Furdui", "Ibuprofen");
	assert(service.getAll().size() == 1);
	service.undo();
	assert(service.getAll().size() == 0);
	service.add("Theraflu", 100, "Marc", "Paracetamol");
	service.modify(1, "Teodor", 50, "Neculau", "Ibuprofen");
	assert(service.getAll().at(0).getDenumire().compare("Teodor") == 0);
	service.undo();
	assert(service.getAll().at(0).getDenumire().compare("Theraflu") == 0);
	service.rmv(1);
	assert(service.getAll().size() == 0);
	service.undo();
	assert(service.getAll().size() == 1);
}

void testRepoFile() {
	try {
		MedicamentRepoFile repo_invalid("file_invalid"); assert(false); }
	catch (RepoException& e) {
		assert(e.getMessage().compare("Nu s-a putut deschide fisierul file_invalid...\n") == 0);
	}
	
	MedicamentRepoFile repo("file_repo_test");
	assert(repo.getAll().size() == 5);
	Medicament m{ "Coldrex", 60, "Anca", "Codeina" };
	repo.store(m);
	Medicament m_mod{ "ColdrexUltra", 40, "Gabi", "Codeina" };
	repo.replace(1, m_mod);
	repo.remove(6);
	try {
		repo.insertAt(m, 10); assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMessage().compare("Pozitie invalida pentru inserare!\n") == 0);
	}
	repo.insertAt(m, 5);
	repo.remove(6);
}