from domain.melodie import Melodie
from repository.melodie_repo import MelodieRepository

class Service:
    """
    clasa care gestioneaza legatura dintre repository si UI si se ocupa de functionalitati
    """
    def __init__(self, m_repository: MelodieRepository):
        self.__m_repository = m_repository

    def initialise_list(self):
        """
        incarca lista cu datele din fisier
        """
        self.__m_repository.loadFromFile()

    def get_lista_melodii(self):
        """
        returneaza lista de melodii
        """
        return self.__m_repository.get_all()

    def modificare_melodie(self, titlu, artist, gen, data):
        """
        modifica genul si data aparitiei pentru melodia specificata
        """
        self.__m_repository.validare_modificare(gen, data)
        self.__m_repository.modificare(titlu, artist, gen, data)
        self.__m_repository.updateFile()

    def statistica1(self):
        """
        prima statistica
        """
        veche, noua = self.__m_repository.veche_noua()
        return veche, noua

    def statistica2(self):
        """
        a doua statistica
        """
        return self.__m_repository.melodii_per_gen()

    def statistica3(self):
        """
        a treia statistica
        """
        artist, max = self.__m_repository.artistul_max()
        return artist, max