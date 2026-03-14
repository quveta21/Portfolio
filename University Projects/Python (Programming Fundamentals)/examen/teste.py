import unittest

from controller.service import Service
from domain.melodie import Melodie
from repository.melodie_repo import MelodieRepository, ValidateGenData


class TestRepository(unittest.TestCase):
    def setUp(self):
        self.m_repo = MelodieRepository("melodii.txt")

    def testRepository(self):
        self.assertEqual(self.m_repo.get_all(), [])
        try:
            self.m_repo.loadFromFile()
            assert True
        except IOError:
            assert False
        try:
            self.m_repo.updateFile()
            assert True
        except IOError:
            assert False
        self.m_repo.modificare("titlu1","artist1","Jazz","22.1.2018")
        self.assertEqual(self.m_repo.get_all()[0].get_gen(),"Jazz")
        self.assertEqual(self.m_repo.get_all()[0].get_data(), "22.1.2018")
        with self.assertRaises(ValidateGenData) as context:
            self.m_repo.validare_modificare("salut","123.5.1020")
        self.assertEqual(str(context.exception), "Genul si data introduse sunt invalide!")
        veche, noua = self.m_repo.veche_noua()
        self.assertEqual(veche.get_titlu(), "titlu8")
        self.assertEqual(noua.get_data(), "26.5.2024")
        self.assertEqual(self.m_repo.melodii_per_gen(), "4 Rock, 3 Pop, 3 Jazz")

class TestService(unittest.TestCase):
    def setUp(self):
        self.service = Service(MelodieRepository("melodii.txt"))

    def testService(self):
        self.service.initialise_list()
        self.assertEqual(self.service.statistica3(), ("artist2", 4))