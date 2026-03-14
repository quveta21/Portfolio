from controller.service import Service
from domain.country import CountryStats
from repository.country_repo import DuplicateException


class ConsoleUI:
    """
    clasa care gestioneaza interfata utilizatorului
    """
    def __init__(self, service: Service):
        """
        initializeaza cu un service
        """
        self.__service = service

    def meniu(self):
        print("1. Adaugare statistica")
        print("2. Afisare tari care au rata de inflatie mai mica decat un nr citit de la tastatura + nr max de someri")
        print("3. Exit")

    def addCS(self, name: str, year: str, infl: float, unempl_rate: float, population: int):
        """
        adaugare statistica
        :param: statistica care trebuie adaugata
        :return: se modifica lista si fisierul
        """
        try:
            country = CountryStats(name, year, infl, unempl_rate, population)
            self.__service.addCountryStats(country)
            print("Stats successfully updated")
        except DuplicateException as ex:
            print(ex)

    def inflAvg(self, nr: float):
        """
        afiseaza o lista cu toate tarile care au rata medie de inflatie mai mica decat un nr citit de la tastatura
        :param nr: numarul citit de la tastatura
        :return: se afiseaza in consola
        """
        try:
            countries = self.__service.allInflationAverage(nr)
            for c in countries:
                print(c)
        except BaseException as ex:
            print(ex)

    def run(self):
        """
        rularea aplicatiei. executarea functionalitatilor conform comenzilor primite + afisare erori
        """
        self.__service.initialiseList()
        run = True
        while run:
            try:
                command = int(input(">>"))
                match command:
                    case 1:
                        name = input("Name: ")
                        year = input("Year: ")
                        infl = float(input("Inflation: "))
                        unempl_rate = float(input("Unemployment Rate: "))
                        population = int(input("Population: "))
                        self.addCS(name, year, infl, unempl_rate, population)
                    case 2:
                        nr = float(input("Average inflation rate smaller than: "))
                        self.inflAvg(nr)
                    case 3:
                        run = False
                        print("Goodbye!")
                        break
                    case _:
                        raise BaseException(f"Command {command} is invalid")

            except BaseException as ex:
                print(ex)