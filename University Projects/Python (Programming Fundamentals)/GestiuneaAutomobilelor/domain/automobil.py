class Automobil:
    def __init__(self, id: int, marca: str, pret: int, model: str, data: list):
        self.__id = id
        self.__marca = marca
        self.__pret = pret
        self.__model = model
        self.__data = data

    def __str__(self):
        return f"{self.__id},{self.__marca},{self.__pret},{self.__model},{self.__data[0]},{self.__data[1]},{self.__data[2]}"

    def get_id(self):
        return self.__id
    def get_marca(self):
        return self.__marca
    def get_pret(self):
        return self.__pret
    def get_model(self):
        return self.__model
    def get_data(self):
        return self.__data

    def set_id(self, id):
        self.__id = id
    def set_marca(self, marca):
        self.__marca = marca
    def set_pret(self, pret):
        self.__pret = pret
    def set_model(self, model):
        self.__model = model
    def set_data(self, data):
        self.__data = data