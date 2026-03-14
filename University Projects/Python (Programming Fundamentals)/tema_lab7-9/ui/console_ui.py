from logging import exception

from controller.service import Service
from domain.disciplina import Disciplina
from domain.student import Student
from utils import combSort, insertionSort


class ConsoleUI:
    """
    clasa pentru interfata cu utilizatorul de tip consola
    citeste de la tastatura, apeleaza functii din service si afiseaza rezultatul acestora
    """
    def __init__(self, service: Service):
        self.__service = service

    def select_mode(self):
        """
        afiseaza variantele de utilizare ale aplicatiei
        """
        print("Selectati una dintre variante inaintea folosirii aplicatiei:")
        print("1. Aplicatia salveaza datele in memorie")
        print("2. Aplicatia salveaza datele in fisiere")

    def meniu(self):
        """
        meniul principal
        """
        print("1. Adauga student")
        print("2. Sterge student")
        print("3. Afiseaza student")
        print("4. Adauga disciplina")
        print("5. Sterge disciplina")
        print("6. Afiseaza discipline")
        print("7. Cautare student")
        print("8. Cautare disciplina")
        print("9. Genereaza student random")
        print("10. Asignare unei note studentului")
        print("11. Afiseaza notele unui student")
        print("12. Lista de studenti si notele lor la o disciplina data ordonat dupa nume")
        print("13. Lista de studenti si notele lor la o disciplina data ordonat dupa nota")
        print("14. Primii 20% din studenti ordonat dupa media notelor la toate disciplinele")
        print("15. Lista studentilor cu media disciplinelor mai mica strict decat 6")
        print("16. Exit")

    def add_student(self, id, name):
        """
        adauga student la lista
        :param id: id-ul studentului
        :param name: numele studentului
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.add_student(id, name)
        except Exception as errors:
            print(errors)

    def add_student_file(self, id, name):
        """
        adauga student la lista
        :param id: id-ul studentului
        :param name: numele studentului
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.add_student_file(id, name)
        except Exception as errors:
            print(errors)

    def delete_student(self, id):
        """
        sterge student din lista
        :param id: id-ul studentului
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.delete_student(id)
        except Exception as errors:
            print(errors)

    def delete_student_file(self, id):
        """
        sterge student din lista
        :param id: id-ul studentului
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.delete_student_file(id)
        except Exception as errors:
            print(errors)

    def afiseaza_studenti(self):
        """
        :return: lista cu studentii
        """
        lista_studenti = []
        for student in self.__service.get_students():
            lista_studenti.append(f"{student.getId()} {student.getNume()}")
        return lista_studenti

    def afiseaza_studenti_file(self):
        """
        :return: lista cu studentii
        """
        lista_studenti = []
        for student in self.__service.get_students_file():
            lista_studenti.append(f"{student.getId()} {student.getNume()}")
        return lista_studenti

    def add_disciplina(self, id, name, profesor):
        """
        adauga disciplinei la lista
        :param id: id-ul disciplinei
        :param name: numele disciplinei
        :param profesor: numele profesorului
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.add_disciplina(id, name, profesor)
        except Exception as errors:
            print(errors)

    def add_disciplina_file(self, id, name, profesor):
        """
        adauga disciplinei la lista
        :param id: id-ul disciplinei
        :param name: numele disciplinei
        :param profesor: numele profesorului
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.add_disciplina_file(id, name, profesor)
        except Exception as errors:
            print(errors)

    def delete_disciplina(self, id):
        """
        sterge disciplina din lista
        :param id: id-ul disciplinei
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.delete_disciplina(id)
        except Exception as errors:
            print(errors)

    def delete_disciplina_file(self, id):
        """
        sterge disciplina din lista
        :param id: id-ul disciplinei
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.delete_disciplina_file(id)
        except Exception as errors:
            print(errors)

    def afiseaza_discipline(self):
        """
        :return: lista cu disciplinele
        """
        lista_discipline = []
        for disciplina in self.__service.get_discipline():
            lista_discipline.append(f"{disciplina.getId()} {disciplina.getNume()} {disciplina.getProfesor()}")
        return lista_discipline

    def afiseaza_discipline_file(self):
        """
        :return: lista cu disciplinele
        """
        lista_discipline = []
        for disciplina in self.__service.get_discipline_file():
            lista_discipline.append(f"{disciplina.getId()} {disciplina.getNume()} {disciplina.getProfesor()}")
        return lista_discipline

    def add_nota(self, student: Student, disciplina: Disciplina, valoare: float):
        """
        :param student: studentul care primeste nota
        :param disciplina: disciplina la care primeste nota
        :param valoare: valoarea notei
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.add_nota(student, disciplina, valoare)
        except Exception as errors:
            print(errors)

    def add_nota_file(self, student: Student, disciplina: Disciplina, valoare: float):
        """
        :param student: studentul care primeste nota
        :param disciplina: disciplina la care primeste nota
        :param valoare: valoarea notei
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        try:
            self.__service.add_nota_file(student, disciplina, valoare)
        except Exception as errors:
            print(errors)

    def getNoteStudent(self, studID):
        """
        afiseaza lista cu notele studentului la fiecare disciplina
        :param studID: ID-ul studentului
        :return: toate notele asignate studentului
        """
        try:
            grades = self.__service.getAllGradesForStud(studID, None, None)
            print(f"Notele studentului/studentei: {grades[0].getstName()}")
            for gr in grades:
                print(gr)
        except Exception as errors:
            print(errors)

    def getNoteStudent_file(self, studID):
        """
        afiseaza lista cu notele studentului la fiecare disciplina
        :param studID: ID-ul studentului
        :return: toate notele asignate studentului
        """
        try:
            grades = self.__service.getAllGradesForStud_file(studID)
            print(f"Notele studentului/studentei: {grades[0].getstName()}")
            for gr in grades:
                print(gr)
        except Exception as errors:
            print(errors)

    def getNoteDisciplina(self, discID):
        """
        afiseaza lista cu notele studentilor la o disciplina data
        :param discID: ID-ul disciplinei
        :return: toate notele studentilor la acea disciplina
        """
        try:
            grades = self.__service.getAllGradesForDisc(discID)
            #for gr in grades:
            #   print(gr)
            return grades
        except Exception as errors:
            print(errors)

    def getNoteDisciplina_file(self, discID):
        """
        afiseaza lista cu notele studentilor la o disciplina data
        :param discID: ID-ul disciplinei
        :return: toate notele studentilor la acea disciplina
        """
        try:
            grades = self.__service.getAllGradesForDisc_file(discID)
            #for gr in grades:
            #   print(gr)
            return grades
        except Exception as errors:
            print(errors)

    def getNoteDisciplinaOrdNume(self, discID):
        """
        afiseaza lista cu notele studentilor la o disciplina data ordonata alfabetic dupa nume
        :param discID: ID-ul disciplinei
        :return: toate notele studentilor ordonate
        """
        discName = self.__service.find_disciplina(discID).split()[0]
        print(f"Notele la disciplina {discName} (alfabetic dupa nume):")
        grades = self.getNoteDisciplina(discID)
        combSort(grades, key = lambda x: x.getNume())
        #for gr in sorted(grades, key = lambda x: x.getNume()):
        for gr in grades:
            print(gr)

    def getNoteDisciplinaOrdNume_file(self, discID):
        """
        afiseaza lista cu notele studentilor la o disciplina data ordonata alfabetic dupa nume
        :param discID: ID-ul disciplinei
        :return: toate notele studentilor ordonate
        """
        discName = self.__service.find_disciplina_file(discID).split()[0]
        print(f"Notele la disciplina {discName} (alfabetic dupa nume):")
        grades = self.getNoteDisciplina_file(discID)
        insertionSort(grades, key = lambda x: x.getNume())
        #for gr in sorted(grades, key = lambda x: x.getNume()):
        for gr in grades:
            print(gr)

    def getNoteDisciplinaOrdNota(self, discID):
        """
        afiseaza lista cu notele studentilor la o disciplina data ordonata dupa nota
        :param discID: ID-ul disciplinei
        :return: toate notele studentilor ordonate
        """
        discName = self.__service.find_disciplina(discID).split()[0]
        print(f"Notele la disciplina {discName} (ordonate dupa nota):")
        grades = self.getNoteDisciplina(discID)
        insertionSort(grades, reversed = True, key = lambda x: x.getNota())
        #for gr in sorted(grades, key = lambda x: x.getNota(), reverse = True):
        for gr in grades:
            print(gr)

    def getNoteDisciplinaOrdNota_file(self, discID):
        """
        afiseaza lista cu notele studentilor la o disciplina data ordonata dupa nota
        :param discID: ID-ul disciplinei
        :return: toate notele studentilor ordonate
        """
        discName = self.__service.find_disciplina_file(discID).split()[0]
        print(f"Notele la disciplina {discName} (ordonate dupa nota):")
        grades = self.getNoteDisciplina_file(discID)
        combSort(grades, reversed = True, key = lambda x: x.getNota())
        #for gr in sorted(grades, key = lambda x: x.getNota(), reverse = True):
        for gr in grades:
            print(gr)

    def afiseazaPrimii20(self):
        """
        lista cu primii 20% studenti ordonat
        :return: lista cu primii 20%
        """
        try:
            lista = self.__service.getListaStudentNota()
            #lista.sort(key = lambda x: x.getNota(), reverse=True)
            combSort(lista, reversed = True, key = lambda x: x.getNota())
            for el in lista[:5]:
                print(el)
        except Exception as errors:
            print(errors)

    def afiseazaPrimii20_file(self):
        """
        lista cu primii 20% studenti ordonat
        :return: lista cu primii 20%
        """
        try:
            lista = self.__service.getListaStudentNota_file()
            #lista.sort(key = lambda x: x.getNota(), reverse=True)
            insertionSort(lista, reversed = True, key = lambda x: x.getNota())
            for el in lista[:5]:
                print(el)
        except Exception as errors:
            print(errors)

    def mediaDiscSub6(self):
        """
        lista studentilor cu media la toate disciplinele strict mai mica decat 6
        :return: lista cu studentii si notele lor
        """
        try:
            lista = self.__service.getListaStudentNota()
            lista_sub6 = []
            for el in lista:
                if el.getNota() < 6:
                    lista_sub6.append(el)
            if len(lista_sub6) == 0:
                print("Nu exista studenti cu media sub 6!!!")
            else:
                for el in lista_sub6:
                    print(el)
        except Exception as errors:
            print(errors)

    def mediaDiscSub6_file(self):
        """
        lista studentilor cu media la toate disciplinele strict mai mica decat 6
        :return: lista cu studentii si notele lor
        """
        try:
            lista = self.__service.getListaStudentNota_file()
            lista_sub6 = []
            for el in lista:
                if el.getNota() < 6:
                    lista_sub6.append(el)
            if len(lista_sub6) == 0:
                print("Nu exista studenti cu media sub 6!!!")
            else:
                for el in lista_sub6:
                    print(el)
        except Exception as errors:
            print(errors)

    def run(self):
        mode = int(input(">>"))
        run = True
        try:
            if mode == 1:
                self.meniu()
                while run:
                    try:
                        comanda = int(input(">>"))
                        match comanda:
                            case 1:
                                id = input("Id Student: ")
                                name = input("Nume: ")
                                self.add_student(id, name)
                            case 2:
                                id = input("Id Student: ")
                                self.delete_student(id)
                            case 3:
                                print(self.afiseaza_studenti())
                            case 4:
                                id = input("Id Disciplina: ")
                                name = input("Nume: ")
                                profesor = input("Profesor: ")
                                self.add_disciplina(id, name, profesor)
                            case 5:
                                id = input("Id Disciplina: ")
                                self.delete_disciplina(id)
                            case 6:
                                print(self.afiseaza_discipline())
                            case 7:
                                id = input("Id Student: ")
                                print(self.__service.find_student(id))
                            case 8:
                                id = input("Id Disciplina: ")
                                print(self.__service.find_disciplina(id))
                            case 9:
                                self.__service.add_random_student()
                            case 10:
                                id_stud = input("Id Student: ")
                                nume_stud = self.__service.find_student(id_stud)
                                id_disc = input("Id Disciplina: ")
                                nume_disc = self.__service.find_disciplina(id_disc).split()[0]
                                profesor = self.__service.find_disciplina(id_disc).split()[1]
                                valoare = float(input("Nota: "))
                                student = Student(id_stud, nume_stud)
                                disciplina = Disciplina(id_disc, nume_disc, profesor)
                                self.add_nota(student, disciplina, valoare)
                            case 11:
                                id_stud = input("Id Student: ")
                                self.getNoteStudent(id_stud)
                            case 12:
                                id_disc = input("Id Disciplina: ")
                                self.getNoteDisciplinaOrdNume(id_disc)
                            case 13:
                                id_disc = input("Id Disciplina: ")
                                self.getNoteDisciplinaOrdNota(id_disc)
                            case 14:
                                self.afiseazaPrimii20()
                            case 15:
                                self.mediaDiscSub6()
                            case 16:
                                run = False
                                break
                            case _:
                                raise BaseException(f"Comanda {comanda} nu e valida!!!")
                    except BaseException as e:
                        print(e)
            if mode == 2:
                self.meniu()
                self.__service.initialise_student_list()
                self.__service.initialise_disciplina_list()
                self.__service.initialise_nota_list()
                while run:
                    try:
                        comanda = int(input(">>"))
                        match comanda:
                            case 1:
                                id = input("Id Student: ")
                                name = input("Nume: ")
                                self.add_student_file(id, name)
                            case 2:
                                id = input("Id Student: ")
                                self.delete_student_file(id)
                            case 3:
                                print(self.afiseaza_studenti_file())
                            case 4:
                                id = input("Id Disciplina: ")
                                name = input("Nume: ")
                                profesor = input("Profesor: ")
                                self.add_disciplina_file(id, name, profesor)
                            case 5:
                                id = input("Id Disciplina: ")
                                self.delete_disciplina_file(id)
                            case 6:
                                print(self.afiseaza_discipline_file())
                            case 7:
                                id = input("Id Student: ")
                                print(self.__service.find_student_file(id))
                            case 8:
                                id = input("Id Disciplina: ")
                                print(self.__service.find_disciplina_file(id))
                            case 9:
                                self.__service.add_random_student_file()
                            case 10:
                                id_stud = input("Id Student: ")
                                nume_stud = self.__service.find_student_file(id_stud)
                                id_disc = input("Id Disciplina: ")
                                nume_disc = self.__service.find_disciplina_file(id_disc).split()[0]
                                profesor = self.__service.find_disciplina_file(id_disc).split()[1]
                                valoare = float(input("Nota: "))
                                student = Student(id_stud, nume_stud)
                                disciplina = Disciplina(id_disc, nume_disc, profesor)
                                self.add_nota_file(student, disciplina, valoare)
                            case 11:
                                id_stud = input("Id Student: ")
                                self.getNoteStudent_file(id_stud)
                            case 12:
                                id_disc = input("Id Disciplina: ")
                                self.getNoteDisciplinaOrdNume_file(id_disc)
                            case 13:
                                id_disc = input("Id Disciplina: ")
                                self.getNoteDisciplinaOrdNota_file(id_disc)
                            case 14:
                                self.afiseazaPrimii20_file()
                            case 15:
                                self.mediaDiscSub6_file()
                            case 16:
                                run = False
                                break
                            case _:
                                raise BaseException(f"Comanda {comanda} nu e valida!!!")
                    except BaseException as e:
                        print(e)
            else:
                raise BaseException(f"Varianta {mode} nu exista! Va rugam reporniti aplicatia...")
        except BaseException as er:
            print(er)
