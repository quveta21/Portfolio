from domain.automobil import Automobil
from repository.automobil_repo import AutomobilRepository
from datetime import date

class Service:
    def __init__(self, a_repo: AutomobilRepository):
        self.__a_repo = a_repo

    def initialise_list(self):
        self.__a_repo.loadFromFile()

    def adaugare_automobil(self, automobil: Automobil):
        self.__a_repo.addToList(automobil)
        self.__a_repo.updateFile()

    def afisare_automobile(self):
        for a in self.__a_repo.get_lista_curenta():
            print(a)

    def stergere_automobile(self, cifra: int):
        nr = 0
        for a in self.__a_repo.get_lista_curenta():
            pret = a.get_pret()
            while pret > 0:
                if cifra == pret % 10:
                    self.__a_repo.removeFromList(a)
                    nr += 1
                pret //= 10
        if nr > 0:
            self.__a_repo.updateFile()
            return nr
        raise BaseException("No automobiles removed!")

    def check_if_expired(self, a: Automobil):
        inspectia_tehnica = date(int(a.get_data()[2]), int(a.get_data()[1]), int(a.get_data()[0]))
        a_expired = None
        if inspectia_tehnica < date.today():
            a_expired = Automobil(int(a.get_id()), a.get_marca(), int(a.get_pret()), a.get_model(), [int(a.get_data()[0]), int(a.get_data()[1]), int(a.get_data()[2])])
            a_expired.set_marca("*" + a_expired.get_marca())
        if a_expired is None:
            return a
        return a_expired

    def filtrare_automobile(self, text: str, nr: int):
        lista_filtrata = []
        if text == "" and nr == -1:
            raise BaseException("Invalid filter!")
        elif text != "" and nr == -1:
            for a in self.__a_repo.get_lista_curenta():
                if a.get_marca() == text:
                    lista_filtrata.append(self.check_if_expired(a))
            if len(lista_filtrata) == 0:
                raise BaseException("No automobiles found!")
            return lista_filtrata
        elif text == "" and nr != -1:
            for a in self.__a_repo.get_lista_curenta():
                if a.get_pret() <= nr:
                    lista_filtrata.append(self.check_if_expired(a))
            if len(lista_filtrata) == 0:
                raise BaseException("No automobiles found!")
            return sorted(lista_filtrata, key=lambda x: x.get_pret(), reverse=True)
        elif text != "" and nr != -1:
            for a in self.__a_repo.get_lista_curenta():
                if a.get_marca() == text and a.get_pret() <= nr:
                    lista_filtrata.append(self.check_if_expired(a))
            if len(lista_filtrata) == 0:
                raise BaseException("No automobiles found!")
            return sorted(lista_filtrata, key=lambda x: x.get_pret(), reverse=True)

    def undo_service(self):
        self.__a_repo.undo()

    def add_to_undo_service(self):
        self.__a_repo.add_to_undo()