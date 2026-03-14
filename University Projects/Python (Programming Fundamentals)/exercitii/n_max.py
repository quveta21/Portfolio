n = int(input("n = ",))
ap = [0] * 10
while n > 0:
    ap[n % 10] = ap[n % 10] + 1
    n = n // 10
n_max = 0
for i in range(9, -1, -1):
    while ap[i] > 0:
        n_max = n_max * 10 + i
        ap[i] -= 1
print(n_max)
