class CountryStats:
    """
    Clasa care retine statisticile despre o tara
    """
    def __init__(self, name: str, year: str, inflation: float, unemployment_rate: float, population: int):
        """
        creeaza obiect CountryStats cu atributele necesare
        :param name: numele -> str
        :param year: anul -> str
        :param inflation: inflatia -> float
        :param unemployment_rate: unempl. rate -> float
        :param population: populatia -> int
        """
        self.__name = name
        self.__year = year
        self.__inflation = inflation
        self.__unemployment_rate = unemployment_rate
        self.__population = population

    def __str__(self):
        """
        suprascrie str(), folosit la print()
        """
        return f"{self.getName()},{self.getYear()},{self.getInflation()},{self.getUnemploymentRate()},{self.getPopulation()}"

    def getName(self):
        return self.__name

    def getYear(self):
        return self.__year

    def getInflation(self):
        return self.__inflation

    def getUnemploymentRate(self):
        return self.__unemployment_rate

    def getPopulation(self):
        return self.__population

    def setName(self, name: str):
        self.__name = name

    def setYear(self, year: str):
        self.__year = year

    def setInflation(self, inflation: float):
        self.__inflation = inflation

    def setUnemploymentRate(self, unemployment_rate: float):
        self.__unemployment_rate = unemployment_rate

    def setPopulation(self, population: int):
        self.__population = population
