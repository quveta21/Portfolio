from controller.service import Service

class ConsoleUI:
    """
    Clasa care gestioneaza interfata utilizatorului
    """
    def __init__(self, service: Service):
        """
        :param service: service-ul aplicatiei
        """
        self.__service = service

    def menu(self):
        """
        meniul aplicatiei
        """
        print("1. Cautarea camerelor din hotel pe baza tipului (single, double, suite)")
        print("2. Rezervarea unei camere")
        print("3. Exit")

    def afisareCamereGasite(self, tip: str):
        """
        Afiseaza toate camerele care sunt de tipul introdus
        :param tip: tipul(single,double,suite)
        :return: nimic, afiseaza pe ecran camerele
        """
        try:
            tipuri_valide = ["single", "double", "suite"]
            if tip not in tipuri_valide:
                raise Exception("Invalid room type!")
            camere = self.__service.findCamere(tip)
            for c in camere:
                print(c)
        except Exception as ex:
            print(ex)

    def rezervaOfertaAvantajoasa(self, tip: str):
        """
        Rezervarea unei camere
        :param tip: tipul dupa care cauta oferta avantajoasa
        :return: camera cu oferta avantajoasa si se sterge din memorie si fisier camera
        """
        try:
            camera = self.__service.cameraOfertaAvantajoasa(tip)
            print(camera)
            self.__service.rezervaCamera(camera)
        except Exception as ex:
            print(ex)

    def run(self):
        """
        rularea aplicatiei. executarea functionalitatilor conform comenzilor primite + afisare erori
        """
        self.__service.initialiseList()
        run = True
        while run:
            try:
                command = int(input(">>"))
                match command:
                    case 1:
                        tip = input("Room type: ")
                        self.afisareCamereGasite(tip)
                    case 2:
                        tip = input("Room type: ")
                        self.rezervaOfertaAvantajoasa(tip)
                    case 3:
                        run = False
                        print("Goodbye!!!")
                        break
                    case _:
                        raise Exception(f"Command {command} is invalid!")
            except Exception as ex:
                print(ex)