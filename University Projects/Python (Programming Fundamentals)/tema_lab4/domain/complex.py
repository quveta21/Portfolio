import math

class Complex:
    #_total_numere = 0 #atribut static al clasei Complex
    def __init__(self, a, b):
        self.a = a
        self.b = b
    def __str__(self):
        return f"{self.a}+{self.b}i"
    def __eq__(self, other):
        if isinstance(other, Complex):
            return self.a == other.a and self.b == other.b
        return False
    def modul(self):
        return math.sqrt(self.a**2 + self.b**2)
    def __add__(self, other):
        if isinstance(other, Complex):
            return Complex(self.a + other.a, self.b + other.b)
    def __mul__(self, other):
        if isinstance(other, Complex):
            return Complex(self.a * other.a - self.b * other.b, self.a * other.b + self.b * other.a)
            #(a + bi)(c + di) = (ac - bd) + (ad + bc)i