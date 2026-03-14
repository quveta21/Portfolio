from domain.complex import Complex

class InvalidCommand(BaseException):
    pass

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
    return [str(el) for el in lista]

def adauga_in_lista(lista, z):
    """
    adauga la finalul listei un numar complex
    input: lista de nr complexe si un nr complex
    output: lista modificata
    """
    lista.append(z)
    return lista

def inserare_in_lista(lista, z, poz):
    """
    insereaza pe o anumita pozitie din lista un numar complex
    input: lista de nr complexe, nr complex si pozitia
    output: lista modificata
    """
    if not(0 <= poz < len(lista)):
        raise InvalidCommand("Index out of range")
    else:
        lista.insert(poz, z)
        return lista

def stergere_poz(lista, poz):
    """
    sterge un element de pe o pozitie data
    input: lista de nr complexe si pozitia
    output: lista modificata
    """
    if not(0 <= poz < len(lista)):
        raise InvalidCommand("Index out of range")
    else:
        lista.pop(poz)
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
    i = 0
    for el in lista:
        if str(el) == str(z1):
            lista.remove(el)
            lista.insert(i, z2)
        i += 1
    return afiseaza_lista(lista)

def tipareste_parte_imaginara(lista):
    """
    returneaza o lista cu partile imaginare, in ordine, a tuturor elementelor complexe din lista initiala
    input: lista de nr complexe
    output: lista cu partile imaginare
    """
    lista_i = []
    for el in lista:
        lista_i.append(el.b)
    return lista_i

def tipareste_pozitii(lista):
    """
    returneaza o lista cu indicii pozitiilor elementelor din lista initiala
    input: lista de nr complexe
    output: lista de indici
    """
    lista_poz = []
    for i in range(len(lista)):
        lista_poz.append(i)
    return lista_poz

def modul_sub_10(lista):
    """
    returneaza o lista cu toate numerele complexe din lista initiala care au modulul mai mic decat 10
    input: lista de nr complexe
    output: lista noua
    """
    lista_noua = []
    for el in lista:
        if Complex.modul(el) < 10:
            lista_noua.append(str(el))
    return lista_noua

def modul_egal_10(lista):
    """
    returneaza o lista cu toate numerele complexe din lista initiala care au modulul egal cu 10
    input: lista de nr complexe
    output: lista noua
    """
    lista_noua = []
    for el in lista:
        if Complex.modul(el) == 10:
            lista_noua.append(str(el))
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
        s = Complex(0,0)
        for i in range(poz_inc, poz_sf+1):
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
    return sorted(lista, key = lambda z: z.b, reverse = True)

def prim(n):
    """
    verifica primalitatea unui numar
    :param n: numarul de verificat
    :return: 1 daca e prim, 0 altfel
    """
    d = 0
    for i in range(1,n):
        if n%i==0:
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