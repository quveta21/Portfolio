def prim(n):
    d = 0
    for i in range(1,n):
        if n%i==0:
            d = d + 1
    if d == 1:
        return 1
    else:
        return 0

def produs_factori_proprii(n):
    p = 1
    for i in range(2,n):
        if n % i == 0 and prim(i) == 1:
            p *= i
    return p

def test():
    assert produs_factori_proprii(6) == 6
    assert produs_factori_proprii(12) == 6
test()
n = int(input("n = "))
print(produs_factori_proprii(n))
