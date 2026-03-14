def pi_aprox(n=1, m=1025):
    if n==m :
        return 1
    return 6+(2*n+1)**2/pi_aprox(n+1)
pi = 3 + 1/pi_aprox()
print(pi)
