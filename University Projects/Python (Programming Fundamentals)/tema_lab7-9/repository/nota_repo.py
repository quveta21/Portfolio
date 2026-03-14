from domain.disciplina import Disciplina
from domain.nota import Nota
from domain.student import Student


class NotaRepository:
    """
    clasa care gestioneaza toate notele studentilor
    """
    def __init__(self):
        self.__lista_note = []

    def add_nota(self, nota: Nota):
        """
        adauga nota in lista
        :param nota: datele despre nota
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        for n in self.__lista_note:
            if nota.getStudent().getId() == n.getStudent().getId() and nota.getDisciplina().getId() == n.getDisciplina().getId():
                raise BaseException(f"Studentul deja a primit nota {n.getValoare()} la aceasta materie!!!")
        self.__lista_note.append(nota)

    def remove_nota(self, nota: Nota):
        """
        sterge o nota asignata unui student
        :param nota: datele despre nota
        :return: nu returneaza nimic, seteaza lista corespunzator
        """
        self.__lista_note.remove(nota)

    def get_all_note(self):
        """
        :return: lista cu toate notele studentilor
        """
        return self.__lista_note

    def find_nota(self, studID, discID):
        for nota in self.__lista_note:
            if nota.getStudent().getId() == studID and nota.getDisciplina().getId() == discID:
                return nota
        raise BaseException("Nu s-a putut gasi nota!!!")

class NotaFileRepository(NotaRepository):
    """
    Clasa care stocheaza notele in fisier. Derivata din NotaRepository
    """
    def __init__(self, fileName):
        NotaRepository.__init__(self)
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
                    st = Student(attrs[0], attrs[1])
                    disc = Disciplina(attrs[2], attrs[3], attrs[4])
                    nota = Nota(st, disc, float(attrs[5]))
                    super().add_nota(nota)
                    line = file.readline().strip()
        except BaseException as e:
            print(e)
        except IOError as e:
            print(f"Eroare la citirea din fisierul {self.__fileName}...")

    def update_file(self):
        try:
            with (open(self.__fileName, 'w') as file):
                for n in self.get_all_note():
                    n_str = str(n.getStudent().getId()) + " " + n.getStudent().getNume() + " " + str(n.getDisciplina().getId()) + " " + n.getDisciplina.getNume() + " " + n.getDisciplina().getProfesor()+ " " + str(n.getValoare()) + "\n"
                    file.write(n_str)
        except IOError as e:
            print(f"Eroare la actualizarea fisierului {self.__fileName}...")

    def add_nota_to_file(self, nota: Nota):
        """
        adauga nota in fisier
        :param nota: nota care trebuie adaugata
        :return: nimic, se actualizeaza fisierul
        """
        try:
            with open(self.__fileName, 'w') as file:
                super().add_nota(nota)
        except IOError:
            print("Eroare la adaugarea notei in fisier...")
        except Exception as e:
            print(e)
        finally:
            self.update_file()

    def remove_nota_from_file(self, nota: Nota):
        """
        sterge nota din fisier
        :param nota: nota care trebuie stersa
        :return: nimic, se actualizeaza fisierul
        """
        try:
            with open(self.__fileName, 'w') as file:
                super().remove_nota(nota)
        except IOError:
            print("Eroare la stergerea notei din fisier...")
        finally:
            self.update_file()