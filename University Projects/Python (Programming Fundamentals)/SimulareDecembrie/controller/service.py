from domain.camera import Camera
from repository.camera_repo import CameraRepository

class Service:
    """
    Clasa care gestioneaza service-ul, implementeaza functionalitatile folosind datele din repository
    """
    def __init__(self, c_repo: CameraRepository):
        """
        initializeaza service-ul cu repository-ul
        :param c_repo: repository-ul aplicatiei
        """
        self.__c_repo = c_repo

    def initialiseList(self):
        """
        initializeaza lista cu datele din fisier
        """
        self.__c_repo.loadFromFile()


    def findCamere(self, tip: str):
        """
        Cauta camere pe baza tipului si le returneaza pe toate de acel tip
        :param tip: tipul camerei = {single, double, suite}
        :return: lista cu camerele sau exceptie daca nu gaseste
        """
        camere_cautate = []
        for c in self.__c_repo.getListaCamere():
            if c.getTip() == tip:
                camere_cautate.append(c)
        if len(camere_cautate) == 0:
            raise Exception(f"No {tip} rooms found...")
        return camere_cautate

    def rezervaCamera(self, camera: Camera):
        """
        rezerva camera si o sterge din lista si fisier
        :param camera: camera care trebuie rezervata
        """
        self.__c_repo.removeFromList(camera)
        self.__c_repo.updateFile()

    def cameraOfertaAvantajoasa(self, tip: str):
        """
        returneaza oferta cea mai avantajoasa pentru un tip de camera
        :param tip: tipul camerei = {single, double, suite}
        :return: camera cu oferta cea mai avantajoasa
        """
        return self.__c_repo.ofertaAvantajoasa(tip)
