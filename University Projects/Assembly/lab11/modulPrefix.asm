bits 32

global _prefix

segment data public data use32
    rezultat dd 0

segment code public code use32

    _prefix:
        push EBP
        mov EBP, ESP
        pushad
        
        ;mov EAX, [ESP + 12] ; l1
        mov EAX, [EBP + 16] ; l1
        ;mov EBX, [ESP + 20] ; l2
        mov EBX, [EBP + 24] ; l2
        cmp EAX, EBX ; comparam lungimile sirurilor si retinem in ECX lungimea cea mai mica
        ja l2_mai_mic
        mov ECX, [EBP + 16]
        jmp parcurgere
        
        l2_mai_mic:
        mov ECX, [EBP + 24]
        
        parcurgere:
        cld
        mov ESI, [EBP + 12] ; s1
        mov EBX, [EBP + 20] ; s2
        mov EDI, [EBP + 8] ; mutam adresa prefixului in EDI ca sa stocam caracterul
        again:
        mov AL, [ESI] ; AL <- caracterul din s1
        cmp AL, [EBX] ; comparam caracterele din cele doua siruri si se seteaza zero flag-ul
        jne diferite
        stosb ; adaugam caracterul la prefix
        inc ESI
        inc EBX
        
        diferite:
        loopne again
        
        mov EAX, [EDI]
        mov dword[rezultat], EAX
        
        popad
        mov ESP, EBP
        pop EBP
        
        mov EAX, [rezultat]
        
        ret