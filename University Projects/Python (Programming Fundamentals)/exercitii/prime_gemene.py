def prim(n):
    d = 0
    for i in range(1,n):
        if n%i==0:
            d = d + 1
    if d == 1:
        return 1
    else:
        return 0

n = int(input('n = ',))
ok = False
i = n+1
while ok == False:
    if prim(i) == 1 and prim(i+2) == 1:
        print('(', i, ', ', i+2, ')')
        ok = True
    i = i + 1
    
