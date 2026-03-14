from domain.country import CountryStats

class CountryCRUDException(Exception):
    pass

class DuplicateException(CountryCRUDException):
    def __init__(self):
        """
        initialise
        """
        self.__msg = "Country and year already exists"

    def __str__(self):
        return self.__msg

class CountryRepo:
    """
    clasa care stocheaza toate tarile si statisticile lor
    """
    def __init__(self, fileName):
        self.__country_list = []
        self.__fileName = fileName

    def loadFromFile(self):
        """
        load the info from file
        raise error if there is an error when reading from the file
        """
        try:
            with open(self.__fileName, "r") as file:
                line = file.readline().strip()
                while line != "":
                    attrs = line.split(",")
                    country = CountryStats(attrs[0], attrs[1], attrs[2], attrs[3], attrs[4])
                    self.store(country)
                    line = file.readline().strip()
        except IOError:
            print("Error while reading from the file...(Maybe file does not exist?)")
        except DuplicateException as ex:
            print(ex)

    def store(self, country: CountryStats):
        """
        adauga obj CountryStats in lista din repository
        :param country: obj CountryStats
        :return: seteaza lista corespunzator
        """
        for c in self.__country_list:
            if c.getName() == country.getName() and c.getYear() == country.getYear():
                raise DuplicateException()
        self.__country_list.append(country)
        #self.storeToFile()

    def storeToFile(self):
        """
        adauga lista de obj CountryStats in fisier
        :return: actualizeaza fisierul
        """
        try:
            with open(self.__fileName, 'w') as file:
                for country in self.__country_list:
                    file.write(str(country) + "\n")
        except IOError:
            print("Error! Could not write to file...")

    def getAll(self):
        """
        returneaza lista cu toate statisticile
        """
        return self.__country_list

    def inflationAverage(self, countryName: str) -> float:
        """
        returneaza rata de inflatie pentru o anumita tara
        """
        infl_rate = 0
        count = 0
        for c in self.__country_list:
            if c.getName() == countryName:
                infl_rate += float(c.getInflation())
                count += 1
        return infl_rate / count