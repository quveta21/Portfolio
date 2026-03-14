from domain.camera import Camera

class CameraRepository:
    """
    Clasa care retine lista cu toate camerele disponibile
    """
    def __init__(self, fileName):
        """
        initializeaza repository-ul cu o lista de camere initial vida si un fisier de unde sa incarce datele
        :param fileName: numele fisierului din care citim si stergem informatii
        """
        self.__lista_camere = []
        self.__fileName = fileName

    def getListaCamere(self):
        return self.__lista_camere

    def loadFromFile(self):
        """
        incarca lista de camere cu informatii din fisier sau afiseaza eroare daca e cazul
        """
        try:
            with open(self.__fileName, "r") as file:
                line = file.readline().strip()
                while line != "":
                    attrs = line.split(",")
                    camera = Camera(int(attrs[0]), int(attrs[1]), attrs[2], int(attrs[3]))
                    self.__lista_camere.append(camera)
                    line = file.readline().strip()
        except IOError:
            print("Error while reading from the file...(Maybe file does not exist?)")

    def removeFromList(self, camera: Camera):
        """
        sterge camera rezervata din lista
        :param camera: camera care trebuie stearsa
        :return: seteaza lista corespunzator
        """
        for c in self.__lista_camere:
            if c == camera:
                self.__lista_camere.remove(camera)

    def updateFile(self):
        """
        sterge din memorie si din fisier o camera rezervata
        """
        try:
            with open(self.__fileName, "w") as file:
                for c in self.__lista_camere:
                    file.write(str(c) + "\n")
        except IOError:
            print("Error while writing to the file...(Maybe file does not exist?)")

    def ofertaAvantajoasa(self, tip: str):
        """
        se gaseste camera cu pretul cel mai mic de tipul dorit
        :return: camera gasita + pretul rezervarii
        """
        pret_min = 2**32
        camera_gasita = 0
        for c in self.__lista_camere:
            if c.getTip() == tip:
                if int(c.getPretPeZi()) < pret_min:
                    camera_gasita = c
                    pret_min = int(c.getPretPeZi())
        if camera_gasita == 0:
            raise Exception("There are no rooms of this type...")
        return camera_gasita