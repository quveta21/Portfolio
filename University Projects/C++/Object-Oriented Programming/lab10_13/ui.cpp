#include "ui.h"
#include <iostream>
using std::cin;
using std::cout;

string UIException::getMessage() {
	string errors;
	for (const string& e : msg) {
		errors += e;
	}
	return errors;
}

void UI::meniu() {
	cout << "1. Adaugare\n";
	cout << "2. Stergere\n";
	cout << "3. Modificare\n";
	cout << "4. Afisare\n";
	cout << "5. Cautare\n";
	cout << "6. Filtrare dupa pret\n";
	cout << "7. Filtrare dupa substanta activa\n";
	cout << "8. Sortare (Denumire / Producator / Substanta + Pret)\n";
	cout << "9. Vizualizare reteta\n";
	cout << "10. Adauga la reteta\n";
	cout << "11. Goleste reteta\n";
	cout << "12. Genereaza aleator reteta\n";
	cout << "13. Salveaza reteta in fisier\n";
	cout << "14. Undo\n";
	cout << "0. Exit\n";
	cout << "Introduceti optiunea:\n";
}

int UI::get_int() {
	string linie;
	vector<string> errors;
	getline(cin, linie);
	bool invalid = (linie.empty());
	int nr = 0;
	for (auto& ch : linie) {
		if ('0' <= ch && ch <= '9')
			nr = nr * 10 + (ch - '0');
		else
			invalid = true;	//invalid daca gaseste macar un caracter non cifra
	}
	if (invalid) {
		nr = -1;
	}
	return nr;
}

bool UI::validate(const string& denumire, int pret, const string& producator, const string& substanta) {
	vector<string> errors;
	if (denumire.empty())
		errors.emplace_back("Nu ati introdus o denumire valida!\n");
	if (producator.empty())
		errors.emplace_back("Nu ati introdus un producator valid!\n");
	if (substanta.empty())
		errors.emplace_back("Nu ati introdus o substanta valida!\n");
	if (pret < 0)
		errors.emplace_back("Nu ati introdus un pret valid!\n");
	if (errors.empty())
		return true;
	throw UIException(errors);

}


void UI::startUI() {
	meniu();
	int cmd, run = 1;
	while (run) {
		cout << ">";
		cmd = get_int();
		switch (cmd) {
		case 0:
			cout << "Salutare!\n";
			run = 0;
			break;
		case 1:
			ui_add();
			break;
		case 2:
			ui_remove();
			break;
		case 3:
			ui_modify();
			break;
		case 4:
			ui_afisare();
			break;
		case 5:
			ui_search();
			break;
		case 6:
			ui_filter();
			break;
		case 7:
			ui_filter2();
			break;
		case 8:
			ui_sort();
			break;
		case 9:
			ui_showReteta();
			break;
		case 10:
			ui_addToReteta();
			break;
		case 11:
			ui_emptyReteta();
			break;
		case 12:
			ui_generateReteta();
			break;
		case 13:
			ui_saveReteta();
			break;
		case 14:
			ui_undo();
			break;
		default:
			cout << "Optiunea introdusa nu exista!\n";
			break;
		}
	}
}

void UI::ui_add() {
	string denumire, producator, substanta;
	int pret;
	cout << "Denumire: ";
	getline(cin, denumire);
	cout << "Pret: ";
	pret = get_int();
	cout << "Producator: ";
	getline(cin, producator);
	cout << "Substanta: ";
	getline(cin, substanta);

	try {
		validate(denumire, pret, producator, substanta);
		serv.add(denumire, pret, producator, substanta);
		cout << "Medicamentul a fost adaugat cu succes!\n";
	}
	catch (RepoException& er) {
		cout << er.getMessage();
	}
	catch (UIException& eui) {
		cout << eui.getMessage();
	}
}

void UI::ui_remove() {
	int pozitie;
	cout << "Introduceti al catelea medicament doriti sa fie sters: ";
	pozitie = get_int();
	try {
		serv.rmv(pozitie);
		cout << "Medicamentul a fost sters cu succes!\n";
	}
	catch (RepoException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_modify() {
	int pozitie, pret;
	string denumire, producator, substanta;
	cout << "Introduceti al catelea medicament doriti sa fie modificat: ";
	pozitie = get_int();
	cout << "Denumire noua: ";
	getline(cin, denumire);
	cout << "Pret nou: ";
	pret = get_int();
	cout << "Producator nou: ";
	getline(cin, producator);
	cout << "Substanta noua: ";
	getline(cin, substanta);
	try {
		validate(denumire, pret, producator, substanta);
		serv.modify(pozitie, denumire, pret, producator, substanta);
		cout << "Medicamentul a fost modificat cu succes!\n";
	}
	catch (RepoException& e) {
		cout << e.getMessage();
	}
	catch (UIException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_search() {
	string denumire, producator, substanta;
	int pret;
	cout << "Denumire: ";
	getline(cin, denumire);
	cout << "Pret: ";
	pret = get_int();
	cout << "Producator: ";
	getline(cin, producator);
	cout << "Substanta: ";
	getline(cin, substanta);

	try {
		validate(denumire, pret, producator, substanta);
		const auto& m = serv.search(denumire, producator);
		cout << "Medicamentul a fost gasit!\n";
		cout << "Denumire: " << m.getDenumire() << ", Pret: " << m.getPret()
			<< ", Producator: " << m.getProducator() << ", Substanta: " << m.getSubstanta() << '\n';
	}
	catch (RepoException& e) {
		cout << e.getMessage();
	}
	catch (UIException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_afisare() {
	auto medicamente = serv.getAll();
	if (medicamente.size() > 0)
		for (const Medicament& m : medicamente) {
			cout << "Denumire: " << m.getDenumire() << ", Pret: " << m.getPret()
				<< ", Producator: " << m.getProducator() << ", Substanta: " << m.getSubstanta() << '\n';
		}
	else
		cout << "Nu exista medicamente in lista!\n";
}

void UI::ui_filter() {
	int pret;
	cout << "Pret: ";
	pret = get_int();
	try {
		if (pret < 0)
			throw UIException({ "Nu ati introdus un pret valid!\n" });
		auto lista = serv.filter_pret(pret);
		for (const Medicament& m : lista) {
			cout << "Denumire: " << m.getDenumire() << ", Pret: " << m.getPret()
				<< ", Producator: " << m.getProducator() << ", Substanta: " << m.getSubstanta() << '\n';
		}
	}
	catch (RepoException& e) {
		cout << e.getMessage();
	}
	catch (UIException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_filter2() {
	string substanta;
	cout << "Substanta: ";
	getline(cin, substanta);
	try {
		if (substanta.empty())
			throw UIException({ "Nu ati introdus o substanta valida!\n" });
		auto lista = serv.filter_subst(substanta);
		for (const Medicament& m : lista) {
			cout << "Denumire: " << m.getDenumire() << ", Pret: " << m.getPret()
				<< ", Producator: " << m.getProducator() << ", Substanta: " << m.getSubstanta() << '\n';
		}
	}
	catch (RepoException& e) {
		cout << e.getMessage();
	}
	catch (UIException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_sort() {
	int criteriu;
	cout << "Denumire -> 1, Producator -> 2, Substanta + Pret -> 3\n";
	cout << "Criteriu: ";
	criteriu = get_int();
	vector<Medicament> lista_sortata;
	try {
		switch (criteriu)
		{
		case 1:
			lista_sortata = serv.sort(compare_denumire);
			break;
		case 2:
			lista_sortata = serv.sort(compare_producator);
			break;
		case 3:
			lista_sortata = serv.sort(compare_subst_pret);
			break;
		default:
			cout << "Criteriul nu este valid!\n";
			break;
		}
		for (const Medicament& m : lista_sortata) {
			cout << "Denumire: " << m.getDenumire() << ", Pret: " << m.getPret()
				<< ", Producator: " << m.getProducator() << ", Substanta: " << m.getSubstanta() << '\n';
		}
	}
	catch (RepoException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_showReteta() {
	try {
		const auto& r = reteta.getAll();
		cout << "Numarul total de medicamente din reteta: " << r.size() << '\n';
		for (const Medicament& m : r) {
			cout << "Denumire: " << m.getDenumire() << ", Pret: " << m.getPret()
				<< ", Producator: " << m.getProducator() << ", Substanta: " << m.getSubstanta() << '\n';
		}
	}
	catch (RetetaException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_addToReteta() {
	cout << "Introduceti al catelea element din lista doriti sa fie adaugat in reteta: ";
	const int poz = get_int();
	try {
		if (poz < 0 || (poz - 1 < 0 || poz - 1 >= serv.getAll().size()))
			throw UIException({ "Indicele introdus nu e valid!\n" });
		reteta.addToReteta(serv.getAll().at(poz - 1));
		cout << "Medicamentul a fost adaugat la reteta!\n";
		ui_showReteta();
	}
	catch (UIException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_emptyReteta() {
	try {
		reteta.getAll();
		reteta.emptyReteta();
		cout << "Reteta a fost golita cu succes!\n";
		cout << "Numarul total de medicamente din reteta: 0\n";
	}
	catch (RetetaException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_generateReteta() {
	try {
		cout << "Introduceti numarul de medicamente de adaugat aleatoriu: ";
		const int n = get_int();
		if (n <= 0)
			throw UIException({ "Numarul introdus este invalid!\n" });
		reteta.generateReteta(serv.getAll(), n);
		cout << "Reteta a fost populata cu " << n << " elemente aleatorii din lista!\n";
	}
	catch (UIException& e) {
		cout << e.getMessage();
	}
	catch (RetetaException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_saveReteta() {
	try {
		cout << "Introduceti numele fisierului: ";
		string filename;
		getline(cin, filename);
		reteta.saveToFile(filename);
		cout << "Reteta a fost salvata in fisierul " << filename << "!\n";
	}
	catch (RetetaException& e) {
		cout << e.getMessage();
	}
}

void UI::ui_undo() {
	try {
		serv.undo();
		cout << "S-a efectuat undo cu succes!\n";
	}
	catch (RepoException& e) {
		cout << e.getMessage();
	}
}
