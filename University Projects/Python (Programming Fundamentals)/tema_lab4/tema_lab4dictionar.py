import math

class Complex:
    # _total_numere = 0 #atribut static al clasei Complex
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __str__(self):
        return f"{self.a}+{self.b}i"

    def __eq__(self, other):
        if isinstance(other, Complex):
            return self.a == other.a and self.b == other.b
        return False

    def modul(self):
        return math.sqrt(self.a ** 2 + self.b ** 2)

    def __add__(self, other):
        if isinstance(other, Complex):
            return Complex(self.a + other.a, self.b + other.b)

    def __mul__(self, other):
        if isinstance(other, Complex):
            return Complex(self.a * other.a - self.b * other.b, self.a * other.b + self.b * other.a)
            # (a + bi)(c + di) = (ac - bd) + (ad + bc)i

class InvalidCommand(BaseException):
    pass

def meniu():
    """
    afiseaza meniul cu optiunile disponibile pentru utilizator
    """
    print("1. Adauga numar complex in lista")
    print("2. Modifica elemente din lista")
    print("3. Cautare numere")
    print("4. Operatii cu numere din lista")
    print("5. Filtrare")
    print("6. Iesire din program")

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

def citeste_numar() -> tuple:
    """
    citeste partea reala si partea imaginara a numarului complex si o returneaza
    input:
    output: partea reala a si partea imaginara b
    """
    a = int(input("Parte reala: "))
    b = int(input("Parte imaginara: "))
    return a, b

def afiseaza_lista(lista):
    """
    returneaza forma string a elementelor complexe din lista
    input: o lista de nr complexe
    output: lista cu elemente de tip string
    """
    lista_afisare = {}
    for el in lista.values():
        lista_afisare[len(lista_afisare)] = str(el)
    return lista_afisare
    #return {str(el) for el in lista.values()}

def adauga_in_lista(lista, z):
    """
    adauga la finalul listei un numar complex
    input: lista de nr complexe si un nr complex
    output: lista modificata
    """
    lista[len(lista)] = z
    return lista

def inserare_in_lista(lista, z, poz):
    """
    insereaza pe o anumita pozitie din lista un numar complex
    input: lista de nr complexe, nr complex si pozitia
    output: lista modificata
    """
    if not (0 <= poz < len(lista)):
        raise InvalidCommand("Index out of range")
    else:
        for k in range(len(lista), poz, -1):
            lista[k] = lista[k - 1]
        lista[poz] = z
        return lista

def stergere_poz(lista, poz):
    """
    sterge un element de pe o pozitie data
    input: lista de nr complexe si pozitia
    output: lista modificata
    """
    if not (0 <= poz < len(lista)):
        print("nu stiu ce e aicia")
        raise InvalidCommand("Index out of range")
    else:
        for k in range(poz, len(lista)-1):
            lista[k] = lista[k + 1]
        del lista[len(lista)-1]
        return lista

def stergere_interval(lista, poz_inc, poz_sf):
    """
    sterge elemente de pe un interval de pozitii
    input: lista de nr complexe, pozitia de inceput a intervalului si cea de sfarsit
    output: lista modificata
    """
    if poz_inc < 0 or poz_sf < 0 or poz_inc >= len(lista) or poz_sf >= len(lista):
        raise InvalidCommand("Index out of range")
    else:
        i = poz_inc
        while i <= poz_sf:
            lista.pop(i)
            poz_sf -= 1
        return lista

def inlocuire_in_lista(lista, z1, z2):
    """
    inlocuieste toate aparitiile unui numar complex cu un altul
    input: lista de nr complexe, numarul de inlocuit si numarul cu care se inlocuieste
    output: lista modificata
    """
    #i = 0
    for i in lista:
        if str(lista[i]) == str(z1):
            stergere_poz(lista, i)
            inserare_in_lista(lista, z2, i)
        #i += 1
    return afiseaza_lista(lista)

def tipareste_parte_imaginara(lista):
    """
    returneaza o lista cu partile imaginare, in ordine, a tuturor elementelor complexe din lista initiala
    input: lista de nr complexe
    output: lista cu partile imaginare
    """
    lista_i = []
    for el in lista.values():
        lista_i.append(el.b)
    return lista_i

def tipareste_pozitii(lista):
    """
    returneaza o lista cu indicii pozitiilor elementelor din lista initiala
    input: lista de nr complexe
    output: lista de indici
    """
    lista_poz = []
    for i in lista:
        lista_poz.append(i)
    return lista_poz

def modul_sub_10(lista):
    """
    returneaza o lista cu toate numerele complexe din lista initiala care au modulul mai mic decat 10
    input: lista de nr complexe
    output: lista noua
    """
    lista_noua = {}
    for el in lista.values():
        if Complex.modul(el) < 10:
            lista_noua[len(lista_noua)] = str(el)
    return lista_noua

def modul_egal_10(lista):
    """
    returneaza o lista cu toate numerele complexe din lista initiala care au modulul egal cu 10
    input: lista de nr complexe
    output: lista noua
    """
    lista_noua = {}
    for el in lista.values():
        if Complex.modul(el) == 10:
            lista_noua[len(lista_noua)] = str(el)
    return lista_noua

def suma_subsecventa(lista, poz_inc, poz_sf):
    """
    calculeaza suma numerelor complexe dintr-o subsecventa a listei date
    input: lista de nr complexe, pozitia de inceput si pozitia de sfarsit a subsecventei
    output: suma
    """
    if poz_inc < 0 or poz_sf < 0 or poz_inc >= len(lista) or poz_sf >= len(lista):
        raise InvalidCommand("Index out of range")
    else:
        s = Complex(0, 0)
        for i in range(poz_inc, poz_sf + 1):
            s += lista[i]
        return s

def produs_subsecventa(lista, poz_inc, poz_sf):
    """
    calculeaza produsul numerelor complexe dintr-o subsecventa a listei date
    :param lista: lista de nr complexe
    :param poz_inc: pozitia de inceput a subsecventei
    :param poz_sf: pozitia de sfarsit a subsecventei
    :return: produsul
    """
    if poz_inc < 0 or poz_sf < 0 or poz_inc >= len(lista) or poz_sf >= len(lista):
        raise InvalidCommand("Index out of range")
    else:
        p = Complex(1, 0)
        for i in range(poz_inc, poz_sf + 1):
            p *= lista[i]
        return p

def sort_descr_parte_imaginara(lista):
    """
    returneaza lista sortata descrescator dupa partea imaginara
    input: lista de nr complexe
    output: lista sortata
    """
    return sorted(lista, key=lambda z: z.b, reverse=True)

def prim(n):
    """
    verifica primalitatea unui numar
    :param n: numarul de verificat
    :return: 1 daca e prim, 0 altfel
    """
    d = 0
    for i in range(1, n):
        if n % i == 0:
            d = d + 1
    if d == 1:
        return 1
    else:
        return 0

def filtrare_parte_reala_prim(lista):
    """
    elimina din lista aparitiile numerelor complexe ale caror parte reala este un nr prim
    :param lista: lista de nr complexe
    :return: lista filtrata
    """
    for el in lista[:]:
        if prim(el.a):
            lista.remove(el)
    return lista

def filtrare_modul(lista, op, nr):
    """
    elimina din lista numerele complexe ale caror modul este <, = sau > decat un nr dat
    :param lista: lista de nr complexe
    :param op: un operator de comparare dintre <, = si >
    :param nr: nr cu care se compara modulul
    :return: lista filtrata
    """
    match op:
        case '<':
            for el in lista[:]:
                if Complex.modul(el) < nr:
                    lista.remove(el)
            return lista
        case '=':
            for el in lista[:]:
                if Complex.modul(el) == nr:
                    lista.remove(el)
            return lista
        case '>':
            for el in lista[:]:
                if Complex.modul(el) > nr:
                    lista.remove(el)
            return lista
        case _:
            print("Nu ati introdus un operator corect!")

def handle_command(comanda, lista):
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
                    adauga_in_lista(lista, Complex(a, b))
                    print(afiseaza_lista(lista))
                case 'ii':
                    a, b = citeste_numar()
                    poz = int(input("Pozitia pe care se insereaza numarul(index de la 0): "))
                    inserare_in_lista(lista, Complex(a, b), poz)
                    print(afiseaza_lista(lista))
                case _:
                    raise InvalidCommand(f"Comanda {comanda1} nu e valida!")
        case 2:
            meniu2()
            comanda2 = input(">>")
            match comanda2:
                case 'i':
                    poz = int(input("Pozitia la care se sterge numarul(index de la 0): "))
                    stergere_poz(lista, poz)
                    print(afiseaza_lista(lista))
                case 'ii':
                    poz_inc = int(input("Pozitia de inceput: "))
                    poz_sf = int(input("Pozitia de sfarsit: "))
                    stergere_interval(lista, poz_inc, poz_sf)
                    print(afiseaza_lista(lista))
                case 'iii':
                    print("Numarul de inlocuit:")
                    a1, b1 = citeste_numar()
                    print("Numarul cu care se inlocuieste:")
                    a2, b2 = citeste_numar()
                    #print(inlocuire_in_lista(lista, Complex(a1, b1), Complex(a2, b2)))
                    afiseaza_lista(inlocuire_in_lista(lista, Complex(a1, b1), Complex(a2, b2)))
                case _:
                    raise InvalidCommand(f"Comanda {comanda2} nu e valida!")
        case 3:
            meniu3()
            comanda3 = input(">>")
            match comanda3:
                case 'i':
                    print(tipareste_parte_imaginara(lista))
                    print(tipareste_pozitii(lista))
                case 'ii':
                    print(modul_sub_10(lista))
                case 'iii':
                    print(modul_egal_10(lista))
                case _:
                    raise InvalidCommand(f"Comanda {comanda3} nu e valida!")
        case 4:
            meniu4()
            comanda4 = input(">>")
            match comanda4:
                case 'i':
                    poz_inc = int(input("Pozitia de inceput: "))
                    poz_sf = int(input("Pozitia de sfarsit: "))
                    print(suma_subsecventa(lista, poz_inc, poz_sf))
                case 'ii':
                    poz_inc = int(input("Pozitia de inceput: "))
                    poz_sf = int(input("Pozitia de sfarsit: "))
                    print(produs_subsecventa(lista, poz_inc, poz_sf))
                case 'iii':
                    print(afiseaza_lista(sort_descr_parte_imaginara(lista)))
                case _:
                    raise InvalidCommand(f"Comanda {comanda4} nu e valida!")
        case 5:
            meniu5()
            comanda5 = input(">>")
            match comanda5:
                case 'i':
                    print(afiseaza_lista(filtrare_parte_reala_prim(lista)))
                case 'ii':
                    op = str(input("Un operator de comparare dintre {<, =, >}: "))
                    nr = int(input("Numarul cu care se compara: "))
                    filtrare_modul(lista, op, nr)
                    print(afiseaza_lista(lista))
                case _:
                    raise InvalidCommand(f"Comanda {comanda5} nu e valida!")
        case 6:
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
    lista = {}
    while True:
        try:
            comanda = int(input(">>"))
            if handle_command(comanda, lista):
                break
        except ValueError:
            print("Ne asteptam la un numar intreg!")
        except InvalidCommand as ex:
            print(ex)

def test():
    """
    ruleaza testele din program
    """
    """
    assert afiseaza_lista([Complex(1, 2), Complex(3, 4)]) == ['1+2i', '3+4i']
    assert adauga_in_lista([1, 2, 3], 4) == [1, 2, 3, 4]
    assert inserare_in_lista([1, 2, 3], 4, 1) == [1, 4, 2, 3]
    assert stergere_poz([1, 2, 3, 4], 2) == [1, 2, 4]
    assert stergere_interval([1, 2, 3, 4, 5], 1, 3) == [1, 5]
    assert inlocuire_in_lista(['2+2i', '2+2i', '5+5i'], Complex(2, 2), Complex(4, 4)) == ['4+4i', '4+4i', '5+5i']
    assert tipareste_parte_imaginara([Complex(2, 1), Complex(3, 3), Complex(5, 9)]) == [1, 3, 9]
    assert tipareste_pozitii([1, 2, 3, 4]) == [0, 1, 2, 3]
    assert modul_sub_10([Complex(2, 3), Complex(13, 12), Complex(4, 4)]) == ['2+3i', '4+4i']
    assert modul_egal_10([Complex(2, 3), Complex(6, 8), Complex(4, 4)]) == ['6+8i']
    assert suma_subsecventa([Complex(2, 3), Complex(4, 6)], 0, 1) == Complex(6, 9)
    assert produs_subsecventa([Complex(2, 2), Complex(3, 4)], 0, 1) == Complex(-2, 14)
    assert sort_descr_parte_imaginara([Complex(2, 2), Complex(3, 4), Complex(5, 1)]) == [Complex(3, 4), Complex(2, 2),
                                                                                         Complex(5, 1)]
    assert filtrare_parte_reala_prim([Complex(5, 2), Complex(7, 3), Complex(6, 6)]) == [Complex(6, 6)]
    assert filtrare_modul([Complex(2, 5), Complex(5, 3), Complex(9, 9)], '<', 6) == [Complex(9, 9)]
    """

if __name__ == "__main__":
    test()
    meniu()
    start_ui()