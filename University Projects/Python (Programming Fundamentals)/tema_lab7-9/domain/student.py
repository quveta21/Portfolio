class Student:
    """
    clasa care retine date despre un student
    """
    def __init__(self, idStudent, nume):
        self.__idStudent = idStudent
        self.__nume = nume

    def __str__(self):
        return f"ID:{self.__idStudent} Nume:{self.__nume}"

    def getId(self):
        """
        :return: id-ul studentului
        """
        return self.__idStudent

    def getNume(self):
        """
        :return: numele studentului
        """
        return self.__nume

    def setId(self, id):
        """
        :param id: id-ul care trebuie atribuit studentului
        :return: nu returneaza nimic, seteaza id-ul studentului
        """
        self.__idStudent = id

    def setNume(self, nume):
        """
        :param nume: numele care trebuie atribuit studentului
        :return: nu returneaza nimic, seteaza numele studentului
        """
        self.__nume = nume


    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Student):
            return False
        return self.__idStudent == other.__idStudent
