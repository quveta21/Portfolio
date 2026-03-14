n = int(input("n = "))
pal = 0
while n > 0:
    pal = pal * 10 + n%10
    n //= 10
print(pal)
