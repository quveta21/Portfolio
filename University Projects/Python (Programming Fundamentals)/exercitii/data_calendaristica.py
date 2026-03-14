an = int(input("anul: "))
nr = int(input("nr de ordine: "))
luni = [31,28,31,30,31,30,31,31,30,31,30,31]
if an % 400 == 0 or (an % 4 == 0 and an % 100 != 0):
    luni[1] = luni[1] + 1
s = 0
i = 0
while s < nr:
    s = s + luni[i]
    i = i + 1
zi = luni[i-1] - (s - nr)
luna = i
print(zi, '/', luna, '/', an)
