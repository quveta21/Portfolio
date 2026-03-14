def insertionSort(lista, reversed = False, key = lambda x: x):
    n = len(lista)

    if n <= 1:
        return

    for i in range(1, n):
        k = lista[i]
        j = i - 1
        while j >= 0 and ((not reversed and key(k) < key(lista[j])) or (reversed and key(k) > key(lista[j]))):
            lista[j+1] = lista[j]
            j -= 1
        lista[j+1] = k

def getNextGap(gap):
    """
    shrink factor
    """
    gap = (gap*10)//13
    if gap < 1:
        return 1
    return gap

def combSort(lista, reversed = False, key = lambda x: x):
    n = len(lista)
    gap = n
    swapped = True
    while gap != 1 or swapped:
        gap = getNextGap(gap)
        swapped = False
        for i in range(0, n-gap):
            if (not reversed and key(lista[i]) > key(lista[i + gap])) or (reversed and key(lista[i]) < key(lista[i + gap])):
                lista[i], lista[i + gap] = lista[i + gap], lista[i]
                swapped = True