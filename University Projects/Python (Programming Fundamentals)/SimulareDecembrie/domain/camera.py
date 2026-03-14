class Camera:
    """
    Clasa care retine informatiile despre o camera
    """
    def __init__(self, numar: int, etaj: int, tip: str, pret_pe_zi: int):
        """
        initializeaza obiectul Camera cu numarul camerei, etajul, tipul (single,double,suite) si pretul pe o zi
        """
        self.__numar = numar
        self.__etaj = etaj
        self.__tip = tip
        self.__pret_pe_zi = pret_pe_zi

    def __str__(self):
        """
        suprascrie functia str folosita la print()
        :return: formatul dorit pentru afisarea informatiilor despre camera
        """
        return f"{self.getNumar()},{self.getEtaj()},{self.getTip()},{self.getPretPeZi()}"

    def getNumar(self):
        return self.__numar

    def getEtaj(self):
        return self.__etaj

    def getTip(self):
        return self.__tip

    def getPretPeZi(self):
        return self.__pret_pe_zi

    def setNumar(self, numar: int):
        self.__numar = numar

    def setEtaj(self, etaj: int):
        self.__etaj = etaj

    def setTip(self, tip: str):
        self.__tip = tip

    def setPretPeZi(self, pret_pe_zi: int):
        self.__pret_pe_zi = pret_pe_zi
