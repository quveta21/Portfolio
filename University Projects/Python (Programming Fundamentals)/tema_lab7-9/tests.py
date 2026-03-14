import unittest

from domain.student import Student
from domain.disciplina import Disciplina
from domain.nota import Nota
from domain.disciplina_validator import DisciplinaValidator
from controller.service import Service
from domain.student_validator import StudentValidator
from repository.disciplina_repo import DisciplinaRepository, DisciplinaFileRepository
from repository.notaDTO import NotaDTO
from repository.student_repo import StudentRepository, StudentFileRepository
from repository.nota_repo import NotaRepository, NotaFileRepository
from domain.nota_validator import NotaValidator
"""
def tests():

    student = Student("1234", "Alex")
    assert student.getId() == "1234"
    assert student.getNume() == "Alex"
    student.setId("0000")
    student.setNume("Marius")
    assert student.getId() == "0000"
    assert student.getNume() == "Marius"

    disciplina = Disciplina("1111", "Matematica", "Berinde")
    assert disciplina.getId() == "1111"
    assert disciplina.getNume() == "Matematica"
    assert disciplina.getProfesor() == "Berinde"
    disciplina.setId("2222")
    disciplina.setNume("ASC")
    disciplina.setProfesor("Vancea")
    assert disciplina.getId() == "2222"
    assert disciplina.getNume() == "ASC"
    assert disciplina.getProfesor() == "Vancea"

    s_repo = StudentRepository()
    s_repo.add_student(student)
    assert s_repo.get_all_studenti() == [student]
    assert s_repo.find_student_id("0000") == "Marius"
    assert s_repo.find_student_name("Marius") == "0000"
    s_repo.remove_student(student)
    assert s_repo.get_all_studenti() == []

    d_repo = DisciplinaRepository()
    d_repo.add_disciplina(disciplina)
    assert d_repo.get_all_discipline() == [disciplina]
    assert d_repo.find_disciplina_id("2222") == "ASC Vancea"
    assert d_repo.find_disciplina_name("ASC") == "ASC Vancea"
    assert d_repo.find_disciplina_profesor("Vancea") == "ASC Vancea"
    d_repo.remove_disciplina(disciplina)
    assert d_repo.get_all_discipline() == []

    s_repo.add_student(student)
    d_repo.add_disciplina(disciplina)
    s_val = StudentValidator()
    d_val = DisciplinaValidator()
    n_repo = NotaRepository()
    n_val = NotaValidator()
    s_file_repo = StudentFileRepository("student_file")
    service = Service(s_file_repo, s_repo, d_repo, n_repo, s_val, d_val, n_val)
    service.add_nota(student, disciplina, 7.0)
    #assert service.getAllGradesForStud("0000") == [NotaDTO("0000", "Marius", "ASC", "7.0")]
    assert service.get_students() == [student]
    student2 = Student("3333", "Ionut")
    service.add_student("3333", "Ionut")
    assert service.get_students() == [student, student2]
    disciplina2 = Disciplina("8888", "Logica", "Andreea")
    service.add_disciplina("8888", "Logica", "Andreea")
    #assert service.get_discipline() == [disciplina, disciplina2]
    """

class TestStudentDomain(unittest.TestCase):
    def setUp(self):
        """
        code executed before each test
        """
        self.student_id = "1234"
        self.student_name = "Alex"
        self.student = Student(self.student_id, self.student_name)

    def testStudentDomain(self):
        self.assertEqual(self.student.getId(), self.student_id)
        self.assertEqual(self.student.getNume(), self.student_name)
        self.student.setId("5678")
        self.assertEqual(self.student.getId(), "5678")
        self.student.setNume("Marius")
        self.assertEqual(self.student.getNume(), "Marius")

class TestStudentValidator(unittest.TestCase):
    def setUp(self):
        self.student_id_invalid = "12"
        self.student_name_invalid = ""
        self.student_invalid = Student(self.student_id_invalid, self.student_name_invalid)
        self.student_id = "1234"
        self.student_name = "Alex"
        self.student = Student(self.student_id, self.student_name)
        self.s_val = StudentValidator()

    def testStudentValidator(self):
        with self.assertRaises(Exception) as context:
            self.s_val.validate_student(self.student_invalid)
        self.assertEqual(str(context.exception), "Numele studentului este invalid!!!\nId-ul studentului este invalid!!!")

        try:
            self.s_val.validate_student(self.student)
            assert True
        except Exception:
            assert False

class TestStudentRepository(unittest.TestCase):
    def setUp(self):
        self.repository = StudentRepository()
        self.id1 = "1234"
        self.nume1 = "Alex"
        self.student1 = Student(self.id1, self.nume1)
        self.id2 = "5678"
        self.nume2 = "Marius"
        self.student2 = Student(self.id2, self.nume2)
        self.id3 = "1234"
        self.nume3 = "Ionut"
        self.student3 = Student(self.id3, self.nume3)

    def testStudentRepository(self):
        self.repository.add_student(self.student1)
        self.assertEqual(self.repository.get_all_studenti(), [self.student1])
        self.repository.add_student(self.student2)
        self.assertEqual(self.repository.get_all_studenti(), [self.student1, self.student2])
        with self.assertRaises(Exception) as context:
            self.repository.add_student(self.student3)
        self.assertEqual(str(context.exception), "ID-ul 1234 exista deja!!!")
        self.assertEqual(self.repository.afiseaza_studentii(), "ID:1234 Nume:Alex\nID:5678 Nume:Marius\n")
        self.assertEqual(self.repository.find_student_id(self.id1, None, None), self.nume1)
        self.repository.remove_student(self.student1)
        self.assertEqual(self.repository.get_all_studenti(), [self.student2])

class TestDisciplinaDomain(unittest.TestCase):
    def setUp(self):
        self.id_disc = "2222"
        self.nume = "ASC"
        self.profesor = "Vancea"
        self.disciplina = Disciplina(self.id_disc, self.nume, self.profesor)

    def testDisciplinaDomain(self):
        self.assertEqual(self.disciplina.getId(), self.id_disc)
        self.assertEqual(self.disciplina.getNume(), self.nume)
        self.assertEqual(self.disciplina.getProfesor(), self.profesor)
        self.disciplina.setId("3333")
        self.assertEqual(self.disciplina.getId(), "3333")
        self.disciplina.setNume("Analiza")
        self.assertEqual(self.disciplina.getNume(), "Analiza")
        self.disciplina.setProfesor("Berinde")
        self.assertEqual(self.disciplina.getProfesor(), "Berinde")

class TestDisciplinaValidator(unittest.TestCase):
    def setUp(self):
        self.id_invalid = "5"
        self.nume_invalid = ""
        self.profesor_invalid = ""
        self.disciplina_invalid = Disciplina(self.id_invalid, self.nume_invalid, self.profesor_invalid)
        self.id_disc = "2222"
        self.nume = "ASC"
        self.profesor = "Vancea"
        self.disciplina = Disciplina(self.id_disc, self.nume, self.profesor)
        self.d_val = DisciplinaValidator()

    def testDisciplinaValidator(self):
        with self.assertRaises(Exception) as context:
            self.d_val.validate_disciplina(self.disciplina_invalid)
        self.assertEqual(str(context.exception), "Numele disciplinei este invalid!!!\nProfesorul este invalid!!!\nId-ul disciplinei este invalid!!!")

        try:
            self.d_val.validate_disciplina(self.disciplina)
            assert True
        except Exception:
            assert False

class TestDisciplinaRepository(unittest.TestCase):
    def setUp(self):
        self.repository = DisciplinaRepository()
        self.id1 = "2222"
        self.nume1 = "ASC"
        self.profesor1 = "Vancea"
        self.disciplina1 = Disciplina(self.id1, self.nume1, self.profesor1)
        self.id2 = "4444"
        self.nume2 = "Analiza"
        self.profesor2 = "Berinde"
        self.disciplina2 = Disciplina(self.id2, self.nume2, self.profesor2)
        self.id3 = "2222"
        self.nume3 = "Logica"
        self.profesor3 = "Andreea"
        self.disciplina3 = Disciplina(self.id3, self.nume3, self.profesor3)

    def testDisciplinaRepository(self):
        self.repository.add_disciplina(self.disciplina1)
        self.assertEqual(self.repository.get_all_discipline(), [self.disciplina1])
        self.repository.add_disciplina(self.disciplina2)
        self.assertEqual(self.repository.get_all_discipline(), [self.disciplina1, self.disciplina2])
        with self.assertRaises(Exception) as context:
            self.repository.add_disciplina(self.disciplina3)
        self.assertEqual(str(context.exception), "ID-ul 2222 exista deja!!!")
        self.assertEqual(self.repository.find_disciplina_id("2222"), self.nume1 + " " + self.profesor1)
        with self.assertRaises(BaseException) as context:
            self.repository.find_disciplina_id("1245")
        self.assertEqual(str(context.exception), "Nu exista disciplina!!!")
        self.repository.remove_disciplina(self.disciplina1)
        self.assertEqual(self.repository.get_all_discipline(), [self.disciplina2])

class TestNotaDomain(unittest.TestCase):
    def setUp(self):
        self.student = Student("1234", "Alex")
        self.disciplina = Disciplina("2222", "ASC", "Vancea")
        self.valoare = 7.0
        self.nota = Nota(self.student, self.disciplina, self.valoare)

    def testNotaDomain(self):
        self.assertEqual(self.nota.getStudent(), self.student)
        self.assertEqual(self.nota.getDisciplina(), self.disciplina)
        self.assertEqual(self.nota.getValoare(), self.valoare)
        self.nota.setStudent(Student("5678", "Marius"))
        self.assertEqual(self.nota.getStudent(), Student("5678", "Marius"))
        self.nota.setDisciplina(Disciplina("4444", "Analiza", "Berinde"))
        self.assertEqual(self.nota.getDisciplina(), Disciplina("4444", "Analiza", "Berinde"))
        self.nota.setValoare(9.0)
        self.assertEqual(self.nota.getValoare(), 9.0)

class TestNotaValidator(unittest.TestCase):
    def setUp(self):
        self.n_val = NotaValidator()
        self.student_invalid = Student("21", "")
        self.disciplina_invalid = Disciplina("5", "", "")
        self.valoare_invalid = 12.0
        self.nota_invalid = Nota(self.student_invalid, self.disciplina_invalid, self.valoare_invalid)
        self.student = Student("1234", "Alex")
        self.disciplina = Disciplina("2222", "ASC", "Vancea")
        self.valoare = 7.0
        self.nota = Nota(self.student, self.disciplina, self.valoare)

    def testNotaValidator(self):
        with self.assertRaises(Exception) as context:
            self.n_val.validate_nota(self.nota_invalid)
        self.assertEqual(str(context.exception), "Valoarea notei este invalida!!!\nDatele despre student sunt invalide!!!\nDatele despre disciplina sunt invalide!!!")

        try:
            self.n_val.validate_nota(self.nota)
            assert True
        except Exception:
            assert False

class TestNotaRepository(unittest.TestCase):
    def setUp(self):
        self.repository = NotaRepository()
        self.student1 = Student("1234", "Alex")
        self.disciplina1 = Disciplina("2222", "ASC", "Vancea")
        self.valoare1 = 8.0
        self.nota1 = Nota(self.student1, self.disciplina1, self.valoare1)
        self.student2 = Student("5678", "Marius")
        self.disciplina2 = Disciplina("4444", "Analiza", "Berinde")
        self.valoare2 = 5.0
        self.nota2 = Nota(self.student2, self.disciplina2, self.valoare2)
        self.nota3 = Nota(self.student1, self.disciplina1, 2.0)

    def testNotaRepository(self):
        self.repository.add_nota(self.nota1)
        self.assertEqual(self.repository.get_all_note(), [self.nota1])
        self.repository.add_nota(self.nota2)
        self.assertEqual(self.repository.get_all_note(), [self.nota1, self.nota2])
        with self.assertRaises(BaseException) as context:
            self.repository.add_nota(self.nota3)
        self.assertEqual(str(context.exception), "Studentul deja a primit nota 8.0 la aceasta materie!!!")
        self.assertEqual(self.repository.find_nota("1234", "2222"), self.nota1)
        with self.assertRaises(BaseException) as context:
            self.repository.find_nota("1234", "4444")
        self.assertEqual(str(context.exception), "Nu s-a putut gasi nota!!!")

def run_tests():
    unittest.main()