def P(a, b):
    apa = [0] * 10
    apb = [0] * 10
    while a > 0:
        apa[a % 10] += 1
        a //= 10
    while b > 0:
        apb[b % 10] += 1
        b //= 10
    ok = True
    for i in range(0, 10):
        if (apa[i] and not apb[i]) or (not apa[i] and apb[i]):
            ok = False
    if ok == True:
        return 1
    else:
        return 0

def test():
    assert P(2113, 32123) == 1
    assert P(2123, 789) == 0
    assert P(4441, 14) == 1
    assert P(879, 9989) == 0

test()
a = int(input("a = "))
b = int(input("b = "))
print(P(a, b))
