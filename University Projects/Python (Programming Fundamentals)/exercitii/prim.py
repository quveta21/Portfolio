n = int(input("n = "))
div = 0
for i in range(1,n):
    if(n % i == 0):
        div += 1
if div == 1:
    print("E prim")
else:
    print("Nu e prim")
