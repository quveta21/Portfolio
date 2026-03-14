class Disciplina:
    """
    clasa care retine date despre o disciplina
    """
    def __init__(self, idDisciplina, nume, profesor):
        #self.__idDisciplina = idDisciplina
        #self.__nume = nume
        #self.__profesor = profesor
        self.__data = {"id": idDisciplina, "nume": nume, "profesor": profesor}

    def getId(self):
        """
        :return: id-ul disciplinei
        """
        return self.__data["id"]

    def getNume(self):
        """
        :return: numele disciplinei
        """
        return self.__data["nume"]

    def getProfesor(self):
        """
        :return: profesorul disciplinei
        """
        return self.__data["profesor"]

    def setId(self, id):
        """
        :param id: id-ul care trebuie atribuit disciplinei
        :return: nu returneaza nimic, seteaza id-ul disciplinei
        """
        self.__data["id"] = id

    def setNume(self, nume):
        """
        :param nume: numele care trebuie atribuit disciplinei
        :return: nu returneaza nimic, seteaza numele disciplinei
        """
        self.__data["nume"] = nume

    def setProfesor(self, profesor):
        """
        :param profesor: profesorul care trebuie atribuit disciplinei
        :return: nu returneaza nimic, seteaza profesorul disciplinei
        """
        self.__data["profesor"] = profesor