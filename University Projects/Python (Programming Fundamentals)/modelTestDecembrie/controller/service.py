from domain.country import CountryStats
from repository.country_repo import CountryRepo

class Service:
    """
    clasa Service-ului care gestioneaza implementarea functionalitatilor si foloseste date din Repo
    """
    def __init__(self, c_repo: CountryRepo):
        """
        initializare cu un CountryRepo
        :param c_repo: CountryRepo
        """
        self.__c_repo = c_repo

    def initialiseList(self):
        """
        initializeaza lista de CountryStats cu datele din fisier
        """
        self.__c_repo.loadFromFile()

    def showList(self):
        """
        afiseaza in consola lista de statistici din repo (doar pt verificare)
        """
        for c in self.__c_repo.getAll():
            print(c)

    def addCountryStats(self, country: CountryStats):
        """
        adauga obj CountryStats in lista + fisier
        :param country: obiectul care trebuie adaugat
        :return: seteaza corespunzator lista si afiseaza in fisier
        """
        self.__c_repo.store(country)
        self.__c_repo.storeToFile()

    def nrMaxSomeri(self, countryName: str):
        """
        returneaza nr maxim de someri dintr-un an pentru o anumita tara
        """
        max = 0
        max_population = 0
        for c in self.__c_repo.getAll():
            if c.getName() == countryName:
                if float(c.getUnemploymentRate()) == max and int(c.getPopulation()) > max_population:
                    max_population = float(c.getPopulation())
                elif float(c.getUnemploymentRate()) > max:
                    max = float(c.getUnemploymentRate())
                    max_population = float(c.getPopulation())
        return int(max / 100 * max_population // 1)


    def allInflationAverage(self, nr: float):
        """
        returneaza o lista cu toate tarile care au rata medie de inflatie mai mica decat un nr citit de la tastatura
        """
        countries_approved = []
        countries_verrified = []
        for c in self.__c_repo.getAll():
            infl = self.__c_repo.inflationAverage(c.getName())
            if infl < nr and (c.getName() not in countries_verrified):
                nr_someri = self.nrMaxSomeri(c.getName())
                countries_approved.append(c.getName() + "," + str(nr_someri))
            countries_verrified.append(c.getName())
        if len(countries_approved) == 0:
            raise BaseException(f"Cannot find countries with average inflation rate smaller than {nr}...")
        return countries_approved