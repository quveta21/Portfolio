n = int(input("n = "))
prim = False
m = n
while prim == False:
    m += 1
    div = 0
    for el in range(1,m):
        if(m % el == 0):
            div += 1
    if div == 1:
        prim = True
print(m)
