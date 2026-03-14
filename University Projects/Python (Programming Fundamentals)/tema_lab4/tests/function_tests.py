from domain.complex import Complex
from functionalitati.functii import afiseaza_lista
from functionalitati.functii import adauga_in_lista
from functionalitati.functii import inserare_in_lista
from functionalitati.functii import stergere_poz
from functionalitati.functii import stergere_interval
from functionalitati.functii import inlocuire_in_lista
from functionalitati.functii import tipareste_parte_imaginara
from functionalitati.functii import tipareste_pozitii
from functionalitati.functii import modul_sub_10
from functionalitati.functii import modul_egal_10
from functionalitati.functii import suma_subsecventa
from functionalitati.functii import produs_subsecventa
from functionalitati.functii import sort_descr_parte_imaginara
from functionalitati.functii import filtrare_parte_reala_prim
from functionalitati.functii import filtrare_modul


def test():
    """
    ruleaza testele din program
    """
    assert afiseaza_lista([Complex(1,2), Complex(3,4)]) == ['1+2i', '3+4i']
    assert adauga_in_lista([1,2,3], 4) == [1, 2, 3, 4]
    assert inserare_in_lista([1,2,3], 4, 1) == [1, 4, 2, 3]
    assert stergere_poz([1,2,3,4], 2) == [1, 2, 4]
    assert stergere_interval([1,2,3,4,5], 1, 3) == [1, 5]
    assert inlocuire_in_lista(['2+2i', '2+2i', '5+5i'], Complex(2,2), Complex(4,4)) == ['4+4i', '4+4i', '5+5i']
    assert tipareste_parte_imaginara([Complex(2,1), Complex(3,3), Complex(5,9)]) == [1, 3, 9]
    assert tipareste_pozitii([1,2,3,4]) == [0, 1, 2, 3]
    assert modul_sub_10([Complex(2,3), Complex(13,12), Complex(4,4)]) == ['2+3i', '4+4i']
    assert modul_egal_10([Complex(2,3), Complex(6,8), Complex(4,4)]) == ['6+8i']
    assert suma_subsecventa([Complex(2,3), Complex(4,6)], 0, 1) == Complex(6,9)
    assert produs_subsecventa([Complex(2,2), Complex(3,4)], 0, 1) == Complex(-2,14)
    assert sort_descr_parte_imaginara([Complex(2,2), Complex(3,4), Complex(5,1)]) == [Complex(3,4), Complex(2,2), Complex(5,1)]
    assert filtrare_parte_reala_prim([Complex(5,2), Complex(7,3), Complex(6,6)]) == [Complex(6,6)]
    assert filtrare_modul([Complex(2,5), Complex(5,3), Complex(9,9)], '<', 6) == [Complex(9,9)]
