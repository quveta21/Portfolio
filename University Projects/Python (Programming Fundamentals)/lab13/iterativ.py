"""
Generati bilete la PRONOSPORT pentru un bilet cu n meciuri.
Pronosticurile pentru un meci pot fi 1,X,2. Generati toate variantele astfel incat:
pronosticul de la ultimul meci nu poate fi X si exista un maxim de doua meciuri cu pronosticul 1
"""

pron = ['1','X','2']

def back_iterativ(n):
    for p1 in pron:
        for p2 in pron:
            for p3 in pron:
                possible_sol = [p1, p2, p3]
                if p3 != 'X' and possible_sol.count('1') <= 2:
                    print(''.join(possible_sol))

back_iterativ(3)