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
if n%2==1:
    if prim(n-2) == 1:
        print('(2, ', n-2, ')')
    else:
        print('Nu se poate vere')
else:
    for i in range(3, n//2, 2):
        if prim(i) == 1:
            if prim(n-i) == 1:
                print('(', i, ', ', n-i, ')')
                ok = True
    if ok == False:
        print('Nu se poate varule')
    
