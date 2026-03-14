class NotaDTO:
    def __init__(self, stID, stName, discName, grade):
        self.__stID = stID
        self.__stName = stName
        self.__discName = discName
        self.__grade = grade

    def __str__(self):
        return f"{self.__discName}: {self.__grade}"

    def getstID(self):
        return self.__stID

    def setstID(self, stID):
        self.__stID = stID

    def getstName(self):
        return self.__stName

    def setstName(self, stName):
        self.__stName = stName

    def getdiscName(self):
        return self.__discName

    def setdiscName(self, discName):
        self.__discName = discName

    def getgrade(self):
        return self.__grade

    def setgrade(self, grade):
        self.__grade = grade