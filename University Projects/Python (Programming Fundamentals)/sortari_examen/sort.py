def bubbleSort(lista: list):
    sorted = False
    while not sorted:
        sorted = True
        for i in range(len(lista) - 1):
            if lista[i] > lista[i + 1]:
                lista[i], lista[i + 1] = lista[i + 1], lista[i]
                sorted = False

def cautare_binara_recursiv(lista, element, st, dr):
    if st > dr:
        return -1
    mij = (st + dr) // 2
    if lista[mij] == element:
        return mij
    if element < lista[mij]:
        return cautare_binara_recursiv(lista, element, st, mij - 1)
    if element > lista[mij]:
        return cautare_binara_recursiv(lista, element, mij + 1, dr)

def cautare_binara_iterativ(lista, element):
    st = 0
    dr = len(lista) - 1
    while st <= dr:
        mij = (st + dr) // 2
        if lista[mij] == element:
            return mij
        if element < lista[mij]:
            dr = mij - 1
        if element > lista[mij]:
            st = mij + 1
    return -1

def insertionSort(lista: list):
    for i in range(1, len(lista)):
        k = lista[i]
        j = i - 1
        while j >= 0 and k < lista[j]:
            lista[j + 1] = lista[j]
            j -= 1
        lista[j+1] = k

def selectionSort(lista: list):
    for i in range(0, len(lista) - 1):
        for j in range(i + 1, len(lista)):
            if lista[i] > lista[j]:
                lista[i], lista[j] = lista[j], lista[i]

def partitionare(lista: list, st, dr):
    #pivot -> lista[dr]
    poz = st
    for i in range(st, dr):
        if lista[i] < lista[dr]:
            lista[i], lista[poz] = lista[poz], lista[i]
            poz += 1                                        #mutam elementele mai mici decat pivotul (lista[dr]) in stanga lui
    lista[poz], lista[dr] = lista[dr], lista[poz]           #punem pivotul pe pozitia corespunzatoare
    return poz                                              #returnam pozitia pe care a fost pus pivotul

def quickSort(lista: list, st, dr):
    if st>=dr:
        return lista
    poz = partitionare(lista, st, dr)
    quickSort(lista, st, poz-1)
    quickSort(lista, poz+1, dr)

def merge(listaStanga, listaDreapta):
    """
    interclasarea practic
    """
    listaSortata = []
    i = 0
    j = 0
    while i < len(listaStanga) and j < len(listaDreapta):
        if listaStanga[i] < listaDreapta[j]:
            listaSortata.append(listaStanga[i])
            i += 1
        else:
            listaSortata.append(listaDreapta[j])
            j += 1
    while i < len(listaStanga):
        listaSortata.append(listaStanga[i])
        i += 1
    while j < len(listaDreapta):
        listaSortata.append(listaDreapta[j])
        j += 1
    return listaSortata

def mergeSort(lista):
    if len(lista) <= 1:
        return lista
    mij = len(lista) // 2
    listaStanga = lista[:mij]
    listaDreapta = lista[mij:]

    mergeSort(listaStanga)
    mergeSort(listaDreapta)

    return merge(listaStanga, listaDreapta)

def divideEtImperaProdus(lista, st, dr):
    if st == dr and st % 2 == 0:
        return lista[st]
    else:
        if st < dr:
            mij = (st+dr)//2
            left = divideEtImperaProdus(lista, st, mij)
            right = divideEtImperaProdus(lista, mij+1, dr)
            return left * right
        else:
            return 1

def divideEtImperaReverse(lista):
    if len(lista) <= 1:
        return lista
    mij = len(lista) // 2
    return divideEtImperaReverse(lista[mij:]) + divideEtImperaReverse(lista[:mij])

def deiParitate(lista):
    if len(lista) <= 1:
        return lista[0] % 2 == 0
    mij = len(lista) // 2
    return deiParitate(lista[mij:]) or deiParitate(lista[:mij])

l = [2,5,1,6,3,8,7,9,4]
#bubbleSort(l)
#insertionSort(l)
#selectionSort(l)
quickSort(l, 0, len(l) - 1)
print(l)
print(cautare_binara_recursiv(l,6, 0, len(l)-1))
print(cautare_binara_iterativ(l, 6))

l2 = [1,2,3,4,5,6]
print(divideEtImperaProdus(l2, 0, len(l2)-1))

l3 = ['1','2','3','4']
print(divideEtImperaReverse(l3))

l4 = [1,3,2,7,8]
print(deiParitate(l4))