a = int(input("a = "))
b = int(input("b = "))
for el in range(1, a+1):
    if a % el == 0 and b % el == 0:
        gcd = el
print(gcd)
