from domain.automobil import Automobil

class AutomobilCRUDException(Exception):
    pass

class DuplicateException(AutomobilCRUDException):
    def __init__(self):
        self.__msg = "This ID already exists."

    def __str__(self):
        return self.__msg

class AutomobilRepository:
    def __init__(self, fileName):
        self.__fileName = fileName
        self.__list_manager = {'lista_curenta': [], 'lista_undo': []}

    def get_lista_curenta(self):
        return self.__list_manager['lista_curenta']

    def get_lista_undo(self) -> list:
        return self.__list_manager['lista_undo']

    def set_lista_curenta(self, lista_curenta_noua: list):
        self.__list_manager['lista_curenta'] = lista_curenta_noua

    def set_lista_undo(self, lista_undo_noua: list):
        self.__list_manager['lista_undo'] = lista_undo_noua

    def add_to_undo(self):
        self.get_lista_undo().append([a for a in self.get_lista_curenta()])

    def undo(self):
        if len(self.get_lista_undo()) == 0:
            raise ValueError("Can not undo anymore.")
        self.set_lista_curenta(self.get_lista_undo().pop())
        self.updateFile()

    def loadFromFile(self):
        try:
            with open(self.__fileName, 'r') as file:
                line = file.readline().strip()
                while line != "":
                    attrs = line.split(",")
                    automobil = Automobil(int(attrs[0]), attrs[1], int(attrs[2]), attrs[3], [attrs[4], attrs[5], attrs[6]])
                    self.__list_manager["lista_curenta"].append(automobil)
                    line = file.readline().strip()
        except IOError:
            print("Error while reading from the file...(Maybe file does not exist?)")
        except DuplicateException as ex:
            print(ex)

    def updateFile(self):
        try:
            with open(self.__fileName, 'w') as file:
                for a in self.__list_manager["lista_curenta"]:
                    file.write(str(a) + "\n")
        except IOError:
            print("Error while writing to the file...(Maybe file does not exist?)")

    def addToList(self, automobil: Automobil):
        for a in self.__list_manager["lista_curenta"]:
            if a.get_id() == automobil.get_id():
                raise DuplicateException()
        self.__list_manager["lista_curenta"].append(automobil)

    def removeFromList(self, automobil: Automobil):
        if automobil in self.__list_manager["lista_curenta"]:
            self.__list_manager["lista_curenta"].remove(automobil)
