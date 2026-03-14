from controller.service import Service
from repository.melodie_repo import ValidateData, ValidateGen, ValidateGenData


class ConsoleUI:
    """
    Clasa care gestioneaza interfata utilizatorului
    """
    def __init__(self, service: Service):
        self.__service = service

    def meniu(self):
        """
        meniul aplicatiei cu functionalitatile
        """
        print("1. Modificare melodie")
        print("2. Creeaza aleator melodii")
        print("3. Statistici melodii")
        print("4. Afisare lista melodii")
        print("5. Exit")

    def modificare_ui(self, titlu, artist, gen, data):
        """
        modifica melodia sau afiseaza erorile corespunzatoare
        """
        errors = []
        try:
            self.__service.modificare_melodie(titlu, artist, gen, data)
            print("Melodia a fost modificata cu succes.")
        except BaseException as ex:
            errors.append(str(ex))
        except ValidateGenData as ex:
            errors.append(str(ex))
        except ValidateGen as ex:
            errors.append(str(ex))
        except ValidateData as ex:
            errors.append(str(ex))
        if len(errors) > 0:
            print("\n".join(errors))

    def afisare_melodii(self):
        """
        afiseaza lista cu toate melodiile
        """
        for m in self.__service.get_lista_melodii():
            print(m)

    def statistica1_ui(self):
        """
        afiseaza prima statistica
        """
        cea_mai_veche, cea_mai_noua = self.__service.statistica1()
        print(f"Cea mai veche: {cea_mai_veche}")
        print(f"Cea mai noua: {cea_mai_noua}")

    def statistica2_ui(self):
        """
        afiseaza a doua statistica
        """
        print(self.__service.statistica2())

    def statistica3_ui(self):
        """
        afiseaza a treia statistica
        """
        artist, max = self.__service.statistica3()
        print(f"Artistul cu cele mai multe melodii este {artist}, cu {max} melodii")

    def run(self):
        """
        Rularea aplicatiei si a functionaliatilor
        """
        run = True
        self.__service.initialise_list()
        try:
            while run:
                comanda = int(input(">>"))
                match comanda:
                    case 1:
                        titlu = input("Titlul: ")
                        artist = input("Artistul: ")
                        gen = input("Gen nou: ")
                        data = input("Data noua: ")
                        self.modificare_ui(titlu, artist, gen, data)
                    case 3:
                        self.statistica1_ui()
                        self.statistica2_ui()
                        self.statistica3_ui()
                    case 4:
                        self.afisare_melodii()
                    case 5:
                        run = False
                        print("Salutare!")
                        break
                    case _:
                        raise BaseException(f"Comanda {comanda} nu este valida!")
        except BaseException as ex:
            print(ex)