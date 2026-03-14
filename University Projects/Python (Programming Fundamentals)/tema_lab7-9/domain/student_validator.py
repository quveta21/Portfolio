from domain.student import Student

class StudentValidator:
    """
    Clasa care valideaza un student
    """
    def validate_student(self, s: Student):
        errors = []
        if s.getNume() == "":
            errors.append("Numele studentului este invalid!!!")
        if len(s.getId()) != 4:
            errors.append("Id-ul studentului este invalid!!!")
        if len(errors):
            raise Exception('\n'.join(errors))