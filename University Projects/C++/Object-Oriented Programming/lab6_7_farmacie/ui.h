#include "service.h"
#include "reteta.h"

/*
* Clasa pentru exceptiile din UI
*/
class UIException {
	vector<string> msg;
public:
	UIException(const vector<string>& m) : msg{ m } {
	}
	/*
	* Returneaza mesajul exceptiei - string
	*/
	string getMessage();

	~UIException() = default;
};


/*
* Clasa care gestioneaza interfata utilizatorului
*/
class UI {
private:
	MedList& serv;
	Reteta reteta;
public:
	/*
	* Constructorul interfetei
	*/
	UI(MedList& serv, Reteta reteta = Reteta()) noexcept : serv{ serv } {

	}
	/*
	* Meniul interfetei utilizatorului
	*/
	void meniu();

	/*
	* Porneste interfata efectiva a utilizatorului
	*/
	void startUI();

	/*
	* Preia datele de la tastatura si adauga medicamentul in lista
	* Prinde exceptia daca datele sunt invalide
	*/
	void ui_add();

	/*
	* Preia un numar intreg de la tastatura si sterge medicamentul
	* de pe acea pozitie din lista
	*/
	void ui_remove();

	/*
	* Preia un numar intreg de la tastatura si date despre medicament,
	* modifica medicamentul de pe pozitia respectiva
	*/
	void ui_modify();

	/*
	* Preia de la tastatura denumirea si producatorul si cauta
	* medicamentul in functie de acestea
	*/
	void ui_search();

	/*
	* Afiseaza lista curenta cu medicamente
	*/
	void ui_afisare();

	/*
	* Afiseaza lista filtrata dupa pret
	*/
	void ui_filter();

	/*
	* Afiseaza lista filtrata dupa substanta activa
	*/
	void ui_filter2();

	/*
	* Afiseaza lista sortata dupa un anumit criteriu
	*/
	void ui_sort();

	/*
	* Citeste de la tastatura un numar intreg pozitiv
	* returneaza numarul daca input-ul e valid, -1 altfel
	*/
	int get_int();

	/*
	* Valideaza datele despre medicament primite ca argumente
	*/
	bool validate(const string& denumire, int pret, const string& producator, const string& substanta);

	/*
	* Face undo la ultima operatie efectuata
	*/
	void ui_undo();

	/*
	* Afiseaza reteta curenta
	*/
	void ui_showReteta();

	/*
	* Adauga in reteta medicamentul din lista cu indicele citit de la tastatura
	*/
	void ui_addToReteta();

	/*
	* Goleste reteta curenta
	*/
	void ui_emptyReteta();

	/*
	* Populeaza aleator reteta cu nr de medicamente din lista citit de la tastatura
	*/
	void ui_generateReteta();

	/*
	* Salveaza in fisierul cu numele citit de la tastatura reteta curenta
	*/
	void ui_saveReteta();
};