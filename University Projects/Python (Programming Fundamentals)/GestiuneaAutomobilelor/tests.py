import unittest

from domain.automobil import Automobil
from repository.automobil_repo import AutomobilRepository, DuplicateException


class TestRepository(unittest.TestCase):
    def setUp(self):
        self.a_repo = AutomobilRepository("automobile.txt")
        self.a1 = Automobil(4444, "Renault", 1500, "Clio", [6, 7, 2025])
        self.a2 = Automobil(1111,"Volkswagen",5000,"Golf",[12, 1, 2025])

    def testRepository(self):
        self.assertEqual(self.a_repo.get_lista_curenta(), [])
        self.a_repo.addToList(self.a1)
        self.assertEqual(self.a_repo.get_lista_curenta(), [self.a1])
        self.a_repo.loadFromFile()
        with self.assertRaises(DuplicateException) as context:
            self.a_repo.addToList(self.a2)
        self.assertEqual(str(context.exception), "This ID already exists.")