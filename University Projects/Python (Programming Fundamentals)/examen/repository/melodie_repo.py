from domain.melodie import Melodie
from datetime import date
import random

class ValidateException(Exception):
    pass

class ValidateGenData(ValidateException):
    def __init__(self):
        self.__msg = "Genul si data introduse sunt invalide!"
    def __str__(self):
        return self.__msg

class ValidateGen(ValidateException):
    def __init__(self):
        self.__msg = "Genul introdus este invalid!"
    def __str__(self):
        return self.__msg

class ValidateData(ValidateException):
    def __init__(self):
        self.__msg = "Data introdusa este invalida!"
    def __str__(self):
        return self.__msg

class MelodieRepository:
    """
    Clasa care gestioneaza lista de melodii
    """
    def __init__(self, fileName):
        self.__fileName = fileName
        self.__lista_melodii = []

    def get_all(self):
        return self.__lista_melodii

    def loadFromFile(self):
        """
        incarca lista de melodii cu datele din fisier
        """
        try:
            with open(self.__fileName, 'r') as file:
                line = file.readline().strip()
                while line != "":
                    attrs = line.split(",")
                    melodie = Melodie(attrs[0], attrs[1], attrs[2], attrs[3])
                    self.__lista_melodii.append(melodie)
                    line = file.readline().strip()
        except IOError:
            print("Eroare la citirea din fisier...")

    def updateFile(self):
        """
        modifica datele din fisier in functie de starea curenta a listei de melodii
        """
        try:
            with open(self.__fileName, 'w') as file:
                for melodie in self.__lista_melodii:
                    file.write(str(melodie) + "\n")
        except IOError:
            print("Eroare la updatarea fisierului...")

    def modificare(self, titlu, artist, gen, data):
        """
        Modifica genul si data melodiei, daca melodia exista in lista
        """
        gasit = False
        for m in self.__lista_melodii:
            if m.get_titlu() == titlu and m.get_artist() == artist:
                m.set_gen(gen)
                m.set_data(data)
                gasit = True
        if not gasit:
            raise BaseException("Melodia cautata nu exista!")

    def validare_modificare(self, gen, data):
        """
        Valideaza datele introduse de utilizator si ridica erorile corespunzatoare
        """
        genuri_valide = ["Rock","Pop","Jazz"]
        date_valide = {"1": 31, "2": 28, "3": 31, "4": 30, "5": 31, "6": 30, "7": 31, "8": 31, "9": 30, "10": 31, "11": 30, "12": 31}
        if gen not in genuri_valide:
            zi, luna, an = data.split(".")
            if not(1<=int(zi)<=date_valide[luna]) or not(1 <= int(luna) <= 12)  or int(an) > 2025:
                raise ValidateGenData
            else:
                raise ValidateGen
        else:
            zi, luna, an = data.split(".")
            if not (1 <= int(zi) <= date_valide[luna]) or not (1 <= int(luna) <= 12) or int(an) > 2025:
                raise ValidateData

    def veche_noua(self):
        """
        returneaza cea mai veche si cea mai noua melodie
        """
        min = date.today()
        cea_mai_veche = None
        max = date(2000, 1, 1)
        cea_mai_noua = None
        for melodie in self.__lista_melodii:
            zi, luna, an = melodie.get_data().split(".")
            if date(int(an), int(luna), int(zi)) < min:
                min = date(int(an), int(luna), int(zi))
                cea_mai_veche = melodie
            if date(int(an), int(luna), int(zi)) > max:
                max = date(int(an), int(luna), int(zi))
                cea_mai_noua = melodie
        return cea_mai_veche, cea_mai_noua

    def melodii_per_gen(self):
        """
        returneaza numarul de melodii pentru fiecare gen
        """
        nr = {"Rock": 0, "Pop": 0, "Jazz": 0}
        for melodie in self.__lista_melodii:
            nr[melodie.get_gen()] += 1
        return f"{nr["Rock"]} Rock, {nr["Pop"]} Pop, {nr["Jazz"]} Jazz"

    def artistul_max(self):
        """
        returneaza artistul cu cele mai multe melodii
        """
        a = {}
        for melodie in self.__lista_melodii:
            a[melodie.get_artist()] = 0
        for melodie in self.__lista_melodii:
            a[melodie.get_artist()] += 1
        artist_top = None
        max = 0
        for artist in a:
            if a[artist] > max:
                max = a[artist]
                artist_top = artist
        return artist_top, max