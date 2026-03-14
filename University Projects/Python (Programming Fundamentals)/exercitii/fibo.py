n = int(input("n = ",))
a = 0
b = 1
c = a + b
if n == 0:
    nr = 1
else:
    while c <= n:
        a = b
        b = c
        c = a + b
    nr = c
print(nr)
