from domain.disciplina import Disciplina

class DisciplinaValidator:
    """
    Clasa care valideaza o disciplina
    """
    def validate_disciplina(self, d: Disciplina):
        errors = []
        if d.getNume() == "":
            errors.append("Numele disciplinei este invalid!!!")
        if d.getProfesor() == "":
            errors.append("Profesorul este invalid!!!")
        if len(d.getId()) != 4:
            errors.append("Id-ul disciplinei este invalid!!!")
        if len(errors):
            raise Exception('\n'.join(errors))