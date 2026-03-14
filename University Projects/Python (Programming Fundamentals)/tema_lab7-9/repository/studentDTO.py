class StudentDTO:
    def __init__(self, nume, nota):
        self.__nume = nume
        self.__nota = nota

    def __str__(self):
        return f"{self.__nume}: {self.__nota}"

    def getNume(self):
        return self.__nume

    def getNota(self):
        return self.__nota

    def setNume(self, nume):
        self.__nume = nume

    def setNota(self, nota):
        self.__nota = nota