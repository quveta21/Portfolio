#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "test.h"
#include "ui.h"
#include "VectDinT.h"
#include <memory>

using namespace std;

/*
  Functie folosit in teste
  primeste vector prin valoare -> copy constructor
  returneaza prin valoare -> copy constructor sau move constructor
*/
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
	int totalPrice = 0;
	for (auto el : v) {
		totalPrice += el.getPret();
	}
	Medicament p{ "Nurofen", 50, "Furdui", "Ibuprofen" };
	v.add(p);
	return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
	for (int i = 0; i < cate; i++) {
		Medicament p{ std::to_string(i) + "_type", i + 10, std::to_string(i) + "_spec", "Marius"};
		v.add(p);
	}
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	addPets(v, 100);
	assert(v.size() == 100);
	assert(v.get(50).getDenumire() == "50_type");

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2.get(50).getDenumire() == "50_type");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3.get(50).getDenumire() == "50_type");

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4.get(50).getDenumire() == "50_type");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	//v.insert(v.begin(), MyVector{});

	assert(v.size() == 1);

	MyVector v2;
	addPets(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.size() == 0);

}
template <typename MyVector>
void testAll() {
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}


int main()
{
	testRepoAll();
	testServiceAll();
	testReteta();
	testAll<VectDinNewDeleteT<Medicament>>();
	//MedicamentRepo repo;
	auto repo = new MedicamentRepoFile{"file_repo"};
	auto serv = new MedList{ *repo };
	auto ui = new UI{ *serv };
	ui->startUI();
	delete repo;
	delete serv;
	delete ui;
	_CrtDumpMemoryLeaks();
	return 0;
}