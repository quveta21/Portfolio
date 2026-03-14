from domain.disciplina_validator import DisciplinaValidator
from controller.service import Service
from domain.student_validator import StudentValidator
from repository.disciplina_repo import DisciplinaRepository, DisciplinaFileRepository
from repository.student_repo import StudentRepository, StudentFileRepository
from repository.nota_repo import NotaRepository, NotaFileRepository
from domain.nota_validator import NotaValidator
from ui.console_ui import ConsoleUI

def main():
    s_file_repo = StudentFileRepository("student_file")
    s_repo = StudentRepository()
    d_file_repo = DisciplinaFileRepository("disciplina_file")
    d_repo = DisciplinaRepository()
    n_file_repo = NotaFileRepository("nota_file")
    n_repo = NotaRepository()
    s_val = StudentValidator()
    d_val = DisciplinaValidator()
    n_val = NotaValidator()
    service = Service(s_file_repo, s_repo, d_file_repo, d_repo, n_file_repo, n_repo, s_val, d_val, n_val)
    ui = ConsoleUI(service)
    ui.select_mode()
    ui.run()

if __name__ == '__main__':
    main()