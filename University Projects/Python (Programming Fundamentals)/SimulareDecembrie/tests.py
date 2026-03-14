from controller.service import Service
from repository.camera_repo import CameraRepository
from domain.camera import Camera

class Tests:
    """
    Clasa care se ocupa de testele din program
    """
    def repoTests(self):
        """
        Testele functiilor din repository
        :return: assertion error daca functia nu returneaza rezultatul dorit
        """
        c_repo = CameraRepository("camere.txt")
        assert c_repo.getListaCamere() == []
        camera1 = Camera(11,1,"single",20)
        camera2 = Camera(22,2,"single",25)
        c_repo.getListaCamere().append(camera1)
        c_repo.getListaCamere().append(camera2)
        assert c_repo.getListaCamere() == [camera1, camera2]
        assert c_repo.ofertaAvantajoasa("single") == camera1
        c_repo.removeFromList(camera1)
        assert c_repo.getListaCamere() == [camera2]
        c_repo.loadFromFile()
        lista_camere = []
        with open("camere.txt", "r") as file:
            line = file.readline().strip()
            while line != "":
                lista_camere.append(line)
                line = file.readline().strip()
        #assert c_repo.getListaCamere() == lista_camere

    def serviceTests(self):
        """
        Testele functiilor din service
        :return: assertion error daca functia nu returneaza rezultatul dorit
        """
        c_repo = CameraRepository("camere.txt")
        service = Service(c_repo)
        camera1 = Camera(11, 1, "single", 20)
        camera2 = Camera(22, 2, "single", 25)
        c_repo.getListaCamere().append(camera1)
        c_repo.getListaCamere().append(camera2)
        service.rezervaCamera(camera1)
        assert c_repo.getListaCamere() == [camera2]