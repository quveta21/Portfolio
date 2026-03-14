from domain.complex import Complex
from functionalitati.functii import InvalidCommand
from functionalitati.functii import adauga_in_lista
from functionalitati.functii import afiseaza_lista
from functionalitati.functii import citeste_numar
from functionalitati.functii import filtrare_modul
from functionalitati.functii import filtrare_parte_reala_prim
from functionalitati.functii import inlocuire_in_lista
from functionalitati.functii import inserare_in_lista
from functionalitati.functii import modul_egal_10
from functionalitati.functii import modul_sub_10
from functionalitati.functii import produs_subsecventa
from functionalitati.functii import sort_descr_parte_imaginara
from functionalitati.functii import stergere_interval
from functionalitati.functii import stergere_poz
from functionalitati.functii import suma_subsecventa
from functionalitati.functii import tipareste_parte_imaginara
from functionalitati.functii import tipareste_pozitii
from service import list_manager
from service.list_manager import create_list_manager, set_lista_curenta
from service.list_manager import get_lista_curenta, add_to_undo, undo_ui


def meniu():
    """
    afiseaza meniul cu optiunile disponibile pentru utilizator
    """
    print("1. Adauga numar complex in lista")
    print("2. Modifica elemente din lista")
    print("3. Cautare numere")
    print("4. Operatii cu numere din lista")
    print("5. Filtrare")
    print("6. Undo")
    print("7. Iesire din program")


def meniu1():
    """
    submeniu1
    """
    print("i. Adauga la sfarsitul listei")
    print("ii. Inserare pe o pozitie data")


def meniu2():
    """
    submeniu2
    """
    print("i. Sterge element de pe o pozitie data")
    print("ii. Sterge elemente de pe un interval de pozitii")
    print("iii. Inlocuieste toate aparitiile unui numar complex cu un altul")


def meniu3():
    """
    submeniu3
    """
    print("i. Tipareste partea imaginara pentru numerele din lista + pozitiile")
    print("ii. Tipareste toate numerele complexe care au modulul < 10")
    print("iii. Tipareste toate numerele complexe care au modulul = 10")


def meniu4():
    """
    submeniu4
    """
    print("i. Suma numerelor dintr-o subsecventa data")
    print("ii. Produsul numerelor dintr-o subsecventa data")
    print("iii. Tipareste lista sortata descrescator dupa partea imaginara")


def meniu5():
    """
    submeniu5
    """
    print("i. Filtrare parte reala prim")
    print("ii. Filtrare modul")


def handle_command(comanda, list_manager: dict):
    """
    trateaza comanda primita de la utilizator si
    redirecteaza catre functia care rezolva comanda ceruta
    input: comanda - numar natural din multimea {1, 2, 3, 4, 5, 6}, lista de nr complexe
    output: True daca programul s-a terminat, False altfel
    raises: InvalidCommand cand comanda nu face parte din multimea {1, 2, 3, 4, 5, 6}
    """
    match comanda:
        case 1:
            meniu1()
            comanda1 = input(">>")
            match comanda1:
                case 'i':
                    a, b = citeste_numar()
                    add_to_undo(list_manager)
                    adauga_in_lista(get_lista_curenta(list_manager), Complex(a, b))
                    print(afiseaza_lista(get_lista_curenta(list_manager)))
                case 'ii':
                    a, b = citeste_numar()
                    add_to_undo(list_manager)
                    poz = int(input("Pozitia pe care se insereaza numarul(index de la 0): "))
                    inserare_in_lista(list_manager['lista_curenta'], Complex(a, b), poz)
                    print(afiseaza_lista(list_manager['lista_curenta']))
                case _:
                    raise InvalidCommand(f"Comanda {comanda1} nu e valida!")
        case 2:
            meniu2()
            comanda2 = input(">>")
            match comanda2:
                case 'i':
                    poz = int(input("Pozitia la care se sterge numarul(index de la 0): "))
                    add_to_undo(list_manager)
                    stergere_poz(list_manager['lista_curenta'], poz)
                    print(afiseaza_lista(list_manager['lista_curenta']))
                case 'ii':
                    poz_inc = int(input("Pozitia de inceput: "))
                    poz_sf = int(input("Pozitia de sfarsit: "))
                    add_to_undo(list_manager)
                    stergere_interval(list_manager['lista_curenta'], poz_inc, poz_sf)
                    print(afiseaza_lista(list_manager['lista_curenta']))
                case 'iii':
                    print("Numarul de inlocuit:")
                    a1, b1 = citeste_numar()
                    print("Numarul cu care se inlocuieste:")
                    a2, b2 = citeste_numar()
                    add_to_undo(list_manager)
                    print(inlocuire_in_lista(list_manager['lista_curenta'], Complex(a1, b1), Complex(a2, b2)))
                case _:
                    raise InvalidCommand(f"Comanda {comanda2} nu e valida!")
        case 3:
            meniu3()
            comanda3 = input(">>")
            match comanda3:
                case 'i':
                    add_to_undo(list_manager)
                    print(tipareste_parte_imaginara(list_manager['lista_curenta']))
                    print(tipareste_pozitii(list_manager['lista_curenta']))
                case 'ii':
                    add_to_undo(list_manager)
                    print(modul_sub_10(list_manager['lista_curenta']))
                case 'iii':
                    add_to_undo(list_manager)
                    print(modul_egal_10(list_manager['lista_curenta']))
                case _:
                    raise InvalidCommand(f"Comanda {comanda3} nu e valida!")
        case 4:
            meniu4()
            comanda4 = input(">>")
            match comanda4:
                case 'i':
                    poz_inc = int(input("Pozitia de inceput: "))
                    poz_sf = int(input("Pozitia de sfarsit: "))
                    add_to_undo(list_manager)
                    print(suma_subsecventa(list_manager['lista_curenta'], poz_inc, poz_sf))
                case 'ii':
                    poz_inc = int(input("Pozitia de inceput: "))
                    poz_sf = int(input("Pozitia de sfarsit: "))
                    add_to_undo(list_manager)
                    print(produs_subsecventa(list_manager['lista_curenta'], poz_inc, poz_sf))
                case 'iii':
                    add_to_undo(list_manager)
                    print(afiseaza_lista(sort_descr_parte_imaginara(list_manager['lista_curenta'])))
                case _:
                    raise InvalidCommand(f"Comanda {comanda4} nu e valida!")
        case 5:
            meniu5()
            comanda5 = input(">>")
            match comanda5:
                case 'i':
                    add_to_undo(list_manager)
                    print(afiseaza_lista(filtrare_parte_reala_prim(list_manager['lista_curenta'])))
                case 'ii':
                    op = str(input("Un operator de comparare dintre {<, =, >}: "))
                    nr = int(input("Numarul cu care se compara: "))
                    add_to_undo(list_manager)
                    filtrare_modul(list_manager['lista_curenta'], op, nr)
                    print(afiseaza_lista(list_manager['lista_curenta']))
                case _:
                    raise InvalidCommand(f"Comanda {comanda5} nu e valida!")
        case 6:
            undo_ui(list_manager)
            print(afiseaza_lista(get_lista_curenta(list_manager)))
        case 7:
            print("Salutare!!")
            return True
        case _:
            raise InvalidCommand(f"Comanda {comanda} nu e valida!")
    return False


def start_ui():
    """
    porneste interfata grafica de tip consola si prinde exceptiile legate de tipul valorii introduse
    sau corectitudinea comenzii
    """
    list_manager = create_list_manager()
    while True:
        try:
            comanda = int(input(">>"))
            if handle_command(comanda, list_manager):
                break
        except ValueError:
            print("Ne asteptam la un numar intreg!")
        except InvalidCommand as ex:
            print(ex)


def add(list_manager: dict, a: int, b: int):
    """
    adauga numarul complex la lista
    :param list_manager: dictionarul cu lista curenta si lista undo
    :param a: partea reala
    :param b: partea imaginara
    :return: nu returneaza nimic, face un update la lista curenta
    """
    z = Complex(a, b)
    set_lista_curenta(list_manager, adauga_in_lista(get_lista_curenta(list_manager), z))


def delete(list_manager: dict, poz: int):
    """
    sterge din lista numarul de pe o pozitie data
    :param list_manager: dictionarul cu lista curenta si lista undo
    :param poz: pozitia de pe care se sterge numarul
    :return: nu returneaza nimic, face un update la lista curenta
    """
    set_lista_curenta(list_manager, stergere_poz(get_lista_curenta(list_manager), poz))

def undo_batch(list_manager: dict):
    """
    face undo la ultima operatie efectuata
    :param list_manager: dictionarul cu lista curenta si lista undo
    :return: nu returneaza nimic, face un update la lista curenta
    """
    undo_ui(list_manager)

def filtrare_prim(list_manager: dict):
    """
    filtreaza lista prin eliminare numerelor complexe cu partea reala numar prim
    :param list_manager: dictionarul cu lista curenta si lista undo
    :return: nu returneaza nimic, face un update la lista curenta
    """
    set_lista_curenta(list_manager, filtrare_parte_reala_prim(get_lista_curenta(list_manager)))

def batch_mode():
    """
    primeste mai multe comenzi insiruite si executa toate comenzile corecte
    :return: lista finala dupa toate modificarile
    """
    print("Batch mode: You can use add, delete, filter, undo, exit")
    list_manager = create_list_manager()
    comenzi_valide = {"add": add, "delete": delete, "filter": filtrare_prim, "undo": undo_batch, "exit": exit}
    run = True
    while run:
        comanda = input(">>")
        comenzi = comanda.lower().strip().split()
        i = 0
        while i < len(comenzi):
            if comenzi[i] == "":
                i += 1
                continue
            if comenzi[i] == "exit":
                run = False
                break
            if comenzi[i] in comenzi_valide:
                try:
                    if comenzi[i] == "add":
                        if i + 2 < len(comenzi):
                            try:
                                a = int(comenzi[i + 1])
                                b = int(comenzi[i + 2])
                                add_to_undo(list_manager)
                                comenzi_valide["add"](list_manager, a, b)
                                i += 3
                            except ValueError:
                                print("Eroare!")
                                i += 1
                        else:
                            i += 1
                    if comenzi[i] == "delete":
                        if i + 1 < len(comenzi):
                            try:
                                poz =int(comenzi[i + 1])
                                add_to_undo(list_manager)
                                comenzi_valide["delete"](list_manager, poz)
                                i += 2
                            except ValueError:
                                print("Eroare!")
                                i += 1
                    if comenzi[i] == "filter":
                        add_to_undo(list_manager)
                        comenzi_valide["filter"](list_manager)
                        i += 1
                    if comenzi[i] == "undo":
                        comenzi_valide["undo"](list_manager)
                        i += 1
                except ValueError as e:
                    print(e)
                except IndexError as e:
                    print(e)
            else:
                i += 1
    print(afiseaza_lista(get_lista_curenta(list_manager)))
