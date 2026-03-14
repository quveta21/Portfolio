from domain.student import Student
import string
import random

class StudentRepository:
    """
    clasa care gestioneaza lista studentilor
    """
    def __init__(self):
        self.__lista_studenti = []

    def add_student(self, student: Student):
        """
        :param student: studentul care trebuie adaugat listei
        :return: nu returneaza nimic, seteaza lista de studenti corespunzator
        """
        for s in self.__lista_studenti:
            if s.getId() == student.getId():
                raise Exception(f"ID-ul {student.getId()} exista deja!!!")
        self.__lista_studenti.append(student)

    def generate_id_student(self):
        """
        genereaza id random
        :return: id
        """
        digits = string.digits
        return ''.join(random.choice(digits) for i in range(4))

    def generate_nume_student(self):
        """
        genereaza nume random
        :return: nume
        """
        LETTERS = string.ascii_uppercase
        letters = string.ascii_lowercase
        return ''.join(random.choice(LETTERS) for i in range(1)) + ''.join(random.choice(letters) for i in range(5))

    def remove_student(self, student: Student):
        """
        sterge studentul din lista
        :param student: studentul care trebuie sters
        :return: nu returneaza nimic, seteaza lista de studenti corespunzator
        """
        self.__lista_studenti.remove(student)

    def get_all_studenti(self):
        """
        :return: lista cu studenti
        """
        return self.__lista_studenti

    def afiseaza_studentii(self):
        """
        afiseaza studentii din lista
        :return: string cu lista cu studenti
        """
        lista_string = ""
        for s in self.__lista_studenti:
            lista_string += str(s) + '\n'
        return lista_string

    def find_student_id(self, id, lista, gasit):
        """
        cauta un student dupa id
        :param id: id-ul dupa care cauta studentul
        :return: numele studentului
        """
        """
        for s in self.__lista_studenti:
            if s.getId() == id:
                return s.getNume()
        raise BaseException("Nu exista studentul!!!")
        """
        if lista is None:
            lista = self.__lista_studenti
            gasit = False

        if not lista:
            if not gasit:
                raise BaseException("Nu exista studentul!!!")

        if lista[0].getId() == id:
            gasit = True
            return lista[0].getNume()
        return self.find_student_id(id, lista[1:], gasit)

    def find_student_name(self, nume):
        """
        cauta un student dupa nume
        :param nume: numele dupa care cauta studentul
        :return: id-ul studentului
        """
        for s in self.__lista_studenti:
            if s.getNume() == nume:
                return s.getId()

class StudentFileRepository(StudentRepository):
    """
    Clasa care stocheaza studentii in fisier. Derivata din StudentRepository
    """
    def __init__(self,fileName):
        StudentRepository.__init__(self)
        self.__fileName = fileName

    def load_from_file(self):
        """
        populeaza lista din memorie cu date din fisier
        """
        try:
            with open(self.__fileName, 'r') as file:
                line = file.readline().strip()
                while line != "":
                    attrs = line.split()
                    student = Student(attrs[0], attrs[1])
                    super().add_student(student)
                    line = file.readline().strip()
        except BaseException as e:
            print(e)
        except IOError as e:
            print(f"Eroare la citirea din fisierul {self.__fileName}...")

    def update_file(self):
        try:
            with open(self.__fileName, 'w') as file:
                for s in self.get_all_studenti():
                    s_str = str(s.getId()) + " " + s.getNume() + "\n"
                    file.write(s_str)
        except IOError as e:
            print(f"Eroare la actualizarea fisierului {self.__fileName}...")

    def add_student_to_file(self, student: Student):
        """
        adauga student in fisier
        :param student: studentul care trebuie adaugat
        :return: nimic, se actualizeaza fisierul
        """
        try:
            with open(self.__fileName, 'w') as file:
                super().add_student(student)
        except IOError:
            print("Eroare la adaugarea studentului in fisier...")
        except Exception as e:
            print(e)
        finally:
            self.update_file()

    def remove_student_from_file(self, student: Student):
        """
        sterge student din fisier
        :param student: studentul care trebuie sters
        :return: nimic, se actualizeaza fisierul
        """
        try:
            with open(self.__fileName, 'w') as file:
                super().remove_student(student)
        except IOError:
            print("Eroare la stergerea studentului din fisier...")
        finally:
            self.update_file()