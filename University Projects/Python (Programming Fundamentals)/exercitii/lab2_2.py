zi = int(input("zi = "))
luna = int(input("luna = "))
an = int(input("an = "))
varsta = 2024 - an - 1
if luna < 10:
    varsta += 1
else:
    if luna == 10 and zi <= 3:
        varsta += 1
print(varsta)
