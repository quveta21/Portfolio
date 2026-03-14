bits 32

global prefix

segment code use32 class=code public

    prefix:
        mov EAX, [ESP + 12] ; l1
        mov EBX, [ESP + 20] ; l2
        cmp EAX, EBX ; comparam lungimile sirurilor si retinem in ECX lungimea cea mai mica
        ja l2_mai_mic
        mov ECX, [ESP + 12]
        jmp parcurgere
        
        l2_mai_mic:
        mov ECX, [ESP + 20]
        
        parcurgere:
        cld
        mov ESI, [ESP + 8] ; s1
        mov EBX, [ESP + 16] ; s2
        mov EDI, [ESP + 4] ; mutam adresa prefixului in EDI ca sa stocam caracterul
        again:
        mov AL, [ESI] ; AL <- caracterul din s1
        cmp AL, [EBX] ; comparam caracterele din cele doua siruri si se seteaza zero flag-ul
        jne diferite
        stosb ; adaugam caracterul la prefix
        inc ESI
        inc EBX
        
        diferite:
        loopne again
        
    ret 4*5