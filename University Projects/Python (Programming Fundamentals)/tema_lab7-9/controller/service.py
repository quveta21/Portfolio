from domain.nota_validator import NotaValidator
from domain.disciplina import Disciplina
from domain.student import Student
from domain.nota import Nota
from repository.disciplina_repo import DisciplinaRepository, DisciplinaFileRepository
from repository.student_repo import StudentRepository, StudentFileRepository
from repository.nota_repo import NotaRepository, NotaFileRepository
from repository.notaDTO import NotaDTO
from repository.studentDTO import StudentDTO
from domain.student_validator import StudentValidator
from domain.disciplina_validator import DisciplinaValidator


class Service:
    """
    clasa care gestioneaza Service-ul
    """
    def __init__(self, student_file_repo: StudentFileRepository, student_repo: StudentRepository, disciplina_file_repo: DisciplinaFileRepository,
                    disciplina_repo: DisciplinaRepository, nota_file_repo: NotaFileRepository, nota_repo: NotaRepository,
                 student_validator: StudentValidator, disciplina_validator: DisciplinaValidator, nota_validator : NotaValidator):
        self.__student_file_repo = student_file_repo
        self.__student_repo = student_repo
        self.__disciplina_file_repo = disciplina_file_repo
        self.__disciplina_repo = disciplina_repo
        self.__nota_file_repo = nota_file_repo
        self.__nota_repo = nota_repo
        self.__student_validator = student_validator
        self.__disciplina_validator = disciplina_validator
        self.__nota_validator = nota_validator

    def get_students(self):
        """
        :return: lista cu studenti
        """
        return self.__student_repo.get_all_studenti()

    def get_students_file(self):
        """
        :return: lista cu studenti
        """
        return self.__student_file_repo.get_all_studenti()

    def get_discipline(self):
        """
        :return: lista cu disciplina
        """
        return self.__disciplina_repo.get_all_discipline()

    def get_discipline_file(self):
        """
        :return: lista cu disciplina
        """
        return self.__disciplina_file_repo.get_all_discipline()

    def get_note(self):
        """
        :return: lista cu note
        """
        return self.__nota_repo.get_all_note()

    def get_note_file(self):
        """
        :return: lista cu note
        """
        return self.__nota_file_repo.get_all_note()

    def initialise_student_list(self):
        self.__student_file_repo.load_from_file()

    def initialise_disciplina_list(self):
        self.__disciplina_file_repo.load_from_file()

    def initialise_nota_list(self):
        self.__nota_file_repo.load_from_file()

    def add_student(self, id, nume):
        """
        :param id: id-ul studentului
        :param nume: numele studentului
        :return: nu returneaza nimic, adauga studentul in lista
        """
        student = Student(id, nume)
        self.__student_validator.validate_student(student)
        self.__student_repo.add_student(student)

    def add_student_file(self, id, nume):
        """
        :param id: id-ul studentului
        :param nume: numele studentului
        :return: nu returneaza nimic, adauga studentul in lista
        """
        student = Student(id, nume)
        self.__student_validator.validate_student(student)
        self.__student_file_repo.add_student_to_file(student)

    def add_random_student(self):
        id = self.__student_repo.generate_id_student()
        nume = self.__student_repo.generate_nume_student()
        self.add_student(id, nume)

    def add_random_student_file(self):
        id = self.__student_file_repo.generate_id_student()
        nume = self.__student_file_repo.generate_nume_student()
        self.add_student_file(id, nume)

    def delete_student(self, id):
        """
        :param id: id-ul studentului care trebuie sters din lista
        :return: nu returneaza nimic, sterge studentul din lista
        """
        for s in self.__student_repo.get_all_studenti():
            if s.getId() == id:
                self.__student_repo.remove_student(s)
                break
        raise Exception(f"Nu s-a gasit studentul cu ID-ul {id}...")

    def delete_student_file(self, id):
        """
        :param id: id-ul studentului care trebuie sters din lista
        :return: nu returneaza nimic, sterge studentul din lista
        """
        for s in self.__student_file_repo.get_all_studenti():
            if s.getId() == id:
                self.__student_file_repo.remove_student_from_file(s)
                break
        raise Exception(f"Nu s-a gasit studentul cu ID-ul {id}...")

    def find_student(self, id):
        """
        gaseste studentul dupa id
        :return: studentul cautat
        """
        return self.__student_repo.find_student_id(id, None, None)

    def find_student_file(self, id):
        """
        gaseste studentul dupa id
        :return: studentul cautat
        """
        return self.__student_file_repo.find_student_id(id, None, None)

    def initialise_disciplina_list(self):
        self.__disciplina_file_repo.load_from_file()

    def add_disciplina(self, id, nume, profesor):
        """
        :param id: id-ul disciplinei
        :param nume: numele disciplinei
        :param profesor: profesorul disciplinei
        :return: nu returneaza nimic, adauga disciplina in lista
        """
        disciplina = Disciplina(id, nume, profesor)
        self.__disciplina_validator.validate_disciplina(disciplina)
        self.__disciplina_repo.add_disciplina(disciplina)

    def add_disciplina_file(self, id, nume, profesor):
        """
        :param id: id-ul disciplinei
        :param nume: numele disciplinei
        :param profesor: profesorul disciplinei
        :return: nu returneaza nimic, adauga disciplina in lista
        """
        disciplina = Disciplina(id, nume, profesor)
        self.__disciplina_validator.validate_disciplina(disciplina)
        self.__disciplina_file_repo.add_disciplina_to_file(disciplina)

    def delete_disciplina(self, id):
        """
        :param id: id-ul disciplinei care trebuie stearsa din lista
        :return: nu returneaza nimic, sterge disciplina din lista
        """
        for d in self.__disciplina_repo.get_all_discipline():
            if d.getId() == id:
                self.__disciplina_repo.remove_disciplina(d)
                break
        raise Exception(f"Nu s-a gasit disciplina cu ID-ul {id}...")

    def delete_disciplina_file(self, id):
        """
        :param id: id-ul disciplinei care trebuie stearsa din lista
        :return: nu returneaza nimic, sterge disciplina din lista
        """
        for d in self.__disciplina_file_repo.get_all_discipline():
            if d.getId() == id:
                self.__disciplina_file_repo.remove_disciplina_from_file(d)
                break
        raise Exception(f"Nu s-a gasit disciplina cu ID-ul {id}...")

    def find_disciplina(self, id):
        """
        gaseste disciplina dupa id
        :return: disciplina cautata
        """
        return self.__disciplina_repo.find_disciplina_id(id)

    def find_disciplina_file(self, id):
        """
        gaseste disciplina dupa id
        :return: disciplina cautata
        """
        return self.__disciplina_file_repo.find_disciplina_id(id)

    def add_nota(self, student: Student, disciplina: Disciplina, valoare: float):
        """
        adauga nota in lista notelor
        :param student: studentul care primeste nota
        :param disciplina: disciplina la care se acorda nota
        :param valoare: nota
        :return: nimic, se seteaza lista corespunzator
        """
        self.__student_validator.validate_student(student)
        self.__disciplina_validator.validate_disciplina(disciplina)
        nota = Nota(student, disciplina, valoare)
        self.__nota_validator.validate_nota(nota)
        self.__nota_repo.add_nota(nota)

    def add_nota_file(self, student: Student, disciplina: Disciplina, valoare: float):
        """
        adauga nota in lista notelor
        :param student: studentul care primeste nota
        :param disciplina: disciplina la care se acorda nota
        :param valoare: nota
        :return: nimic, se seteaza lista corespunzator
        """
        self.__student_validator.validate_student(student)
        self.__disciplina_validator.validate_disciplina(disciplina)
        nota = Nota(student, disciplina, valoare)
        self.__nota_validator.validate_nota(nota)
        self.__nota_file_repo.add_nota_to_file(nota)

    def getAllGradesForStud(self, studID, discipline, allGrades):
        """
        se genereaza lista cu toate notele unui student
        :param studID: ID-ul dupa care se identifica studentul
        :return: lista cu notele
        """
        """
        studName = self.__student_repo.find_student_id(studID, None, None)
        discipline = self.__disciplina_repo.get_all_discipline()
        allGrades = []
        for d in discipline:
            nota = self.__nota_repo.find_nota(studID, d.getId())
            if nota is not None:
                grade = NotaDTO(studID, studName, d.getNume(), nota.getValoare())
                allGrades.append(grade)
        return allGrades
        """
        studName = self.__student_repo.find_student_id(studID, None, None)
        if discipline is None:
            discipline = self.__disciplina_repo.get_all_discipline()
            allGrades = []

        if not discipline:
            if not allGrades:
                raise Exception("Studentului nu i s-au atribuit note!!!")
            return allGrades

        nota = self.__nota_repo.find_nota(studID, discipline[0].getId())
        if nota is not None:
            grade = NotaDTO(studID, studName, discipline[0].getNume(), nota.getValoare())
            allGrades.append(grade)
        return self.getAllGradesForStud(studID, discipline[1:], allGrades)


    def getAllGradesForStud_file(self, studID):
        """
        se genereaza lista cu toate notele unui student
        :param studID: ID-ul dupa care se identifica studentul
        :return: lista cu notele
        """
        studName = self.__student_file_repo.find_student_id(studID, None, None)
        discipline = self.__disciplina_file_repo.get_all_discipline()
        allGrades = []
        for d in discipline:
            nota = self.__nota_file_repo.find_nota(studID, d.getId())
            if nota is not None:
                grade = NotaDTO(studID, studName, d.getNume(), nota.getValoare())
                allGrades.append(grade)
        return allGrades

    def getListaStudentNota(self):
        """
        lista cu studentii si media notelor lor la toate disciplinele
        :return: numele si nota studentilor
        """
        lista_studentiDTO = []
        for s in self.__student_repo.get_all_studenti():
            nr = 0
            sum = 0
            for n in self.__nota_repo.get_all_note():
                if n.getStudent() == s:
                    sum += n.getValoare()
                    nr += 1
            if sum:
                sDTO = StudentDTO(s.getNume(), sum/nr)
                lista_studentiDTO.append(sDTO)
        if len(lista_studentiDTO):
            return lista_studentiDTO
        raise BaseException("Nu exista note atribuite studentilor!!!")

    def getListaStudentNota_file(self):
        """
        lista cu studentii si media notelor lor la toate disciplinele
        :return: numele si nota studentilor
        """
        lista_studentiDTO = []
        for s in self.__student_file_repo.get_all_studenti():
            nr = 0
            sum = 0
            for n in self.__nota_file_repo.get_all_note():
                if n.getStudent() == s:
                    sum += n.getValoare()
                    nr += 1
            if sum:
                sDTO = StudentDTO(s.getNume(), sum/nr)
                lista_studentiDTO.append(sDTO)
        if len(lista_studentiDTO):
            return lista_studentiDTO
        raise BaseException("Nu exista note atribuite studentilor!!!")

    def getAllGradesForDisc(self, discID):
        """
        se genereaza lista cu toate notele studentilor la o disciplina data
        :param discID: ID-ul dupa care se identifica disciplina
        :return: lista cu notele
        """
        lista_studentiDTO = []
        for n in self.__nota_repo.get_all_note():
            if n.getDisciplina().getId() == discID:
                sDTO = StudentDTO(n.getStudent().getNume(), n.getValoare())
                lista_studentiDTO.append(sDTO)
        if len(lista_studentiDTO):
            return lista_studentiDTO
        raise BaseException("Nu exista note la aceasta disciplina!!!")

    def getAllGradesForDisc_file(self, discID):
        """
        se genereaza lista cu toate notele studentilor la o disciplina data
        :param discID: ID-ul dupa care se identifica disciplina
        :return: lista cu notele
        """
        lista_studentiDTO = []
        for n in self.__nota_file_repo.get_all_note():
            if n.getDisciplina().getId() == discID:
                sDTO = StudentDTO(n.getStudent().getNume(), n.getValoare())
                lista_studentiDTO.append(sDTO)
        if len(lista_studentiDTO):
            return lista_studentiDTO
        raise BaseException("Nu exista note la aceasta disciplina!!!")