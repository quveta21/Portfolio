class InvalidCommand(BaseException):
    pass

def meniu():
    """
    afiseaza meniul cu optiunile disponibile pentru utilizator
    """
    print("1. Citeste o lista de numere intregi")
    print("2. Gaseste o secventa de lungime maxima care contine cel mult trei valori distincte")
    print("3. Gaseste o secventa de lungime maxima care contine doar numere prime")
    print("4. Gaseste o secventa de lungime maxima in care oricare doua numere consecutive sunt relativ prime intre ele")
    print("5. Iesire din aplicatie")

def prim(n):
    """
    verifica primalitatea unui numar intreg
    input: un numar intreg n
    output: 1 daca e prim, 0 altfel
    """
    d = 0
    for i in range(1, n):
        if n % i == 0:
            d = d + 1
    if d == 1:
        return 1
    else:
        return 0

def celmulttrei(lista: list):
    """
    verifica daca o lista contine cel mult 3 valori distincte
    input: o lista
    output: 1 daca are proprietatea, 0 altfel
    """
    val_distincte = 0
    for i in range(len(lista)):
        if lista[i] not in lista[:i]:
            val_distincte += 1
    if val_distincte == 3:
        return 1
    else:
        return 0

def prime_intre_ele(a, b):
    """
    verifica daca doua numere sunt relativ prime intre ele
    input: doua valori intregi
    output: True daca are proprietatea, False altfel
    """
    m = max(a,b)
    for d in range(2,m+1):
        if a % d == 0 and b % d == 0:
            return 0
    return 1

def handle_command(comanda, lista):
    """
    trateaza comanda primita de la utilizator si
    redirecteaza catre functia care rezolva comanda ceruta
    input: comanda - numar natural din multimea {1, 2, 3, 4}
    output: True daca programul s-a terminat, False altfel
    raises: InvalidCommand cand comanda nu face parte din multimea {1, 2, 3, 4}
    """
    match comanda:
        case 1:
            lista.clear()
            s = str(input("Introduceti elementele listei, separate prin virgula: "))
            s = s.strip().split(',')
            for k in s:
                lista.append(int(k))
        case 2:
            print(proprietatea2(lista))
        case 3:
            print(proprietatea4(lista))
        case 4:
            print(proprietatea3(lista))
        case 5:
            return True
        case _:
            raise InvalidCommand(f"Comanda {comanda} is not valid!")
    return False

def proprietatea2(lista):
    """
    gaseste secventa de lungime maxima cu proprietatea 2 (daca sunt mai multe, le afiseaza pe toate)
    """
    l_max = 0
    sol = []
    n = len(lista)
    for i in range(n):
        for j in range(i+1, n):
            l = 0
            if celmulttrei(lista[i:j + 1]):
                l = j + 1 - i
                if l == l_max:
                    sol.append(lista[i:j + 1])
                if l > l_max:
                    l_max = l
                    sol.clear()
                    sol.append(lista[i:j + 1])
    if l_max == 0:
        return "Nu exista secventa cu proprietatea ceruta!"
    else:
        return sol

def proprietatea4(lista):
    """
    gaseste secventa de lungime maxima cu proprietatea 4 (daca sunt mai multe, le afiseaza pe toate)
    """
    l = 0
    l_max = 0
    sol = []
    n = len(lista)
    for i in range(n):
        if prim(lista[i]):
            l += 1
        else:
            l = 0
        if l == l_max:
            sol.append(lista[i - l + 1: i + 1])
        if l > l_max:
            l_max = l
            sol.clear()
            sol.append(lista[i - l + 1: i + 1])
    if l_max == 0:
        return "Nu exista secventa cu proprietatea ceruta!"
    else:
        return sol

def proprietatea3(lista):
    """
    gaseste secventa de lungime maxima cu proprietatea 3 (daca sunt mai multe, le afiseaza pe toate)
    """
    l = 0
    l_max = 0
    sol = []
    n = len(lista)
    for i in range(n - 1):
        if prime_intre_ele(lista[i], lista[i + 1]):
            if l == 0:
                l += 2
            else:
                l += 1
        else:
            l = 0
        if l == l_max:
            sol.append(lista[i + 1 - l + 1: i + 2])
        if l > l_max:
            l_max = l
            sol.clear()
            sol.append(lista[i + 1 - l + 1: i + 2])
    if l_max == 0:
        return "Nu exista secventa cu proprietatea ceruta!"
    else:
        return sol

def start_ui():
    """
    porneste interfata grafica de tip consola si prinde exceptiile legate de tipul valorii introduse
    sau corectitudinea comenzii
    """
    lista = []
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
    assert prim(17) == 1
    assert prim(20) == 0
    assert celmulttrei([1,2,3,1,1]) == 1
    assert celmulttrei([2,2,2,5]) == 0
    assert prime_intre_ele(-2,4) == 0
    assert prime_intre_ele(5,7) == 1
    assert proprietatea2([1,2,2,3,1,4,5]) == [[1, 2, 2, 3, 1]]
    assert proprietatea4([2,3,5,4,7,11,13]) == [[2, 3, 5], [7, 11, 13]]
    assert proprietatea3([2,3,5,10,8,17,21]) == [[2, 3, 5], [8, 17, 21]]

if __name__ == "__main__":
    test()
    meniu()
    start_ui()