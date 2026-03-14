from domain.nota import Nota

class NotaValidator:
    """
    Clasa care valideaza o nota
    """
    def validate_nota(self, nota: Nota):
        errors = []
        if not 1 <= float(nota.getValoare()) <= 10:
            errors.append("Valoarea notei este invalida!!!")
        if len(nota.getStudent().getId()) != 4 or nota.getStudent().getNume() == "":
            errors.append("Datele despre student sunt invalide!!!")
        if len(nota.getDisciplina().getId()) != 4 or nota.getDisciplina().getNume() == "" or nota.getDisciplina().getProfesor() == "":
            errors.append("Datele despre disciplina sunt invalide!!!")
        if len(errors):
            raise Exception('\n'.join(errors))