"""
Generati bilete la PRONOSPORT pentru un bilet cu n meciuri.
Pronosticurile pentru un meci pot fi 1,X,2. Generati toate variantele astfel incat:
pronosticul de la ultimul meci nu poate fi X si exista un maxim de doua meciuri cu pronosticul 1
"""

pron = ['1','X','2']

def back(lista: list, n: int, nr_de_1 = 0):
    lista.append("")
    for p in pron:
        lista[-1] = p
        new_nr_de_1 = nr_de_1 + (1 if p == '1' else 0)
        if is_consistent(lista, n, new_nr_de_1):
            if is_solution(lista, n):
                print_solution(lista)
            else: back(lista[:], n, new_nr_de_1)


def is_consistent(lista: list, n, nr_de_1) -> bool:
    if len(lista) == n:
        return lista[-1] != 'X' and nr_de_1 <= 2
    return nr_de_1 <= 2

def is_solution(lista: list, n) -> bool:
    return len(lista) == n

def print_solution(lista: list):
    print(''.join(lista))


back([], 4)