from domain.student import Student
from domain.disciplina import Disciplina

class Nota:
    """
    clasa care retine notele studentului
    """
    def __init__(self, student: Student, disciplina: Disciplina, valoare: float):
        self.__student = Student(student.getId(), student.getNume())
        self.__disciplina = Disciplina(disciplina.getId(), disciplina.getNume(), disciplina.getProfesor())
        self.__valoare = valoare

    def getStudent(self):
        """
        :return: studentul caruia ii apartine nota
        """
        return self.__student

    def getDisciplina(self):
        """
        :return: disciplina la care este asignata nota
        """
        return self.__disciplina

    def getValoare(self):
        """
        :return: valoarea notei
        """
        return self.__valoare

    def setStudent(self, student):
        """
        :param student: studentul care primeste nota
        :return: seteaza informatiile despre student
        """
        self.__student = student

    def setDisciplina(self, disciplina):
        """
        :param disciplina: disciplina la care se pune nota
        :return: seteaza informatiile despre disciplina
        """
        self.__disciplina = disciplina

    def setValoare(self, valoare):
        """
        :param valoare: nota atribuita
        :return: seteaza valoarea notei
        """
        self.__valoare = valoare