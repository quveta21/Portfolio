from domain.disciplina import Disciplina

class DisciplinaRepository:
    """
    clasa care gestioneaza lista disciplinelor
    """
    def __init__(self):
        self.__lista_discipline = []

    def add_disciplina(self, disciplina: Disciplina):
        """
        :param disciplina: disciplina care trebuie adaugata listei
        :return: nu returneaza nimic, seteaza lista de discipline corespunzator
        """
        for d in self.__lista_discipline:
            if d.getId() == disciplina.getId():
                raise Exception(f"ID-ul {disciplina.getId()} exista deja!!!")
        self.__lista_discipline.append(disciplina)

    def remove_disciplina(self, disciplina: Disciplina):
        """
        :param disciplina: disciplina care trebuie adaugata listei
        :return: nu returneaza nimic, seteaza lista de discipline corespunzator
        """
        self.__lista_discipline.remove(disciplina)

    def get_all_discipline(self):
        """
        :return: lista de discipline
        """
        return self.__lista_discipline

    def find_disciplina_name(self, nume):
        """
        cauta disciplina dupa nume
        :param nume: numele dupa care cauta
        :return: numele si profesorul disciplinei
        """
        for d in self.__lista_discipline:
            if d.getNume() == nume:
                return d.getNume() + " " + d.getProfesor()

    def find_disciplina_id(self, id):
        """
        cauta disciplina dupa id
        :param id: id-ul dupa care cauta
        :return: numele si profesorul disciplinei
        """
        for d in self.__lista_discipline:
            if d.getId() == id:
                return d.getNume() + " " + d.getProfesor()
        raise BaseException("Nu exista disciplina!!!")

    def find_disciplina_profesor(self, profesor):
        """
        cauta disciplina dupa profesor
        :param profesor: profesorul dupa care cauta
        :return: numele si profesorul disciplinei
        """
        for d in self.__lista_discipline:
            if d.getProfesor() == profesor:
                return d.getNume() + " " + d.getProfesor()

class DisciplinaFileRepository(DisciplinaRepository):
    """
    Clasa care stocheaza disciplinele in fisier. Derivata din DisciplinaRepository
    """
    def __init__(self, fileName):
        DisciplinaRepository.__init__(self)
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
                    disciplina = Disciplina(attrs[0], attrs[1], attrs[2])
                    super().add_disciplina(disciplina)
                    line = file.readline().strip()
        except BaseException as e:
            print(e)
        except IOError as e:
            print(f"Eroare la citirea din fisierul {self.__fileName}...")

    def update_file(self):
        try:
            with open(self.__fileName, 'w') as file:
                for d in self.get_all_discipline():
                    d_str = str(d.getId()) + " " + d.getNume() + " " + d.getProfesor() + "\n"
                    file.write(d_str)
        except IOError as e:
            print(f"Eroare la actualizarea fisierului {self.__fileName}...")

    def add_disciplina_to_file(self, disciplina: Disciplina):
        """
        adauga disciplina in fisier
        :param disciplina: disciplina care trebuie adaugata
        :return: nimic, se actualizeaza fisierul
        """
        try:
            with open(self.__fileName, 'w') as file:
                super().add_disciplina(disciplina)
        except IOError:
            print("Eroare la adaugarea disciplinei in fisier...")
        except Exception as e:
            print(e)
        finally:
            self.update_file()

    def remove_disciplina_from_file(self, disciplina: Disciplina):
        """
        sterge disciplina din fisier
        :param disciplina: disciplina care trebuie stearsa
        :return: nimic, se actualizeaza fisierul
        """
        try:
            with open(self.__fileName, 'w') as file:
                super().remove_disciplina(disciplina)
        except IOError:
            print("Eroare la stergerea disciplinei din fisier...")
        finally:
            self.update_file()