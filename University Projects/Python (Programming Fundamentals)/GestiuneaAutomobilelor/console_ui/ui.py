from controller.service import Service
from domain.automobil import Automobil
from repository.automobil_repo import AutomobilRepository, DuplicateException


class ConsoleUI:
    def __init__(self, service: Service):
        self.__service = service

    def meniu(self):
        print("1. Adaugare de automobil")
        print("2. Stergerea automobilelor")
        print("3. Afisare lista automobile")
        print("4. Filtrarea automobilelor")
        print("5. Undo")
        print("6. Exit")

    def adaugare(self, automobil: Automobil):
        try:
            self.__service.adaugare_automobil(automobil)
            print("Automobile successfully added.")
        except DuplicateException as ex:
            print(ex)

    def stergere(self, cifra: int):
        try:
            nr = self.__service.stergere_automobile(cifra)
            print(f"Deleted {nr} automobiles.")
        except BaseException as ex:
            print(ex)

    def filtrare(self, text: str, nr: int):
        try:
            lista_filtrata = self.__service.filtrare_automobile(text, nr)
            for a in lista_filtrata:
                print(a)
        except BaseException as ex:
            print(ex)

    def undo_ui(self):
        try:
            self.__service.undo_service()
            print("The last action was undone.")
        except ValueError as ex:
            print(ex)

    def add_to_undo_ui(self):
        self.__service.add_to_undo_service()

    def run(self):
        self.__service.initialise_list()
        run = True
        while run:
            try:
                command = int(input(">>"))
                match command:
                    case 1:
                        id = int(input("Id: "))
                        marca = input("Marca: ")
                        pret = int(input("Pret: "))
                        model = input("Model: ")
                        zi = int(input("Zi: "))
                        luna = int(input("Luna: "))
                        an = int(input("An: "))
                        data = [zi, luna, an]
                        automobil = Automobil(id, marca, pret, model, data)
                        self.add_to_undo_ui()
                        self.adaugare(automobil)
                    case 2:
                        cifra = int(input("Cifra: "))
                        self.add_to_undo_ui()
                        self.stergere(cifra)
                    case 3:
                        self.__service.afisare_automobile()
                    case 4:
                        text = input("Text: ")
                        nr = input("Pret: ")
                        if nr == "":
                            self.filtrare(text, -1)
                        else:
                            self.filtrare(text, int(nr))
                    case 5:
                        self.undo_ui()
                    case 6:
                        run = False
                        print("Goodbye!")
                        break
                    case _:
                        raise BaseException(f"Command {command} is not valid!")
            except BaseException as ex:
                print(ex)