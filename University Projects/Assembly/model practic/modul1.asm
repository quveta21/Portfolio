bits 32

global nr_biti_1

segment code use32 class = code public
    nr_biti_1:
        mov EAX, [ESP+4] ; in EAX retinem numarul
        mov EBX, 0 ; in EBX retinem frecventa bitilor 1
        mov EDX, 0 ; in EDX retinem la fiecare pas ultima cifra din EAX
        
        repeta:
        mov EDX, EAX ; copiem EAX-ul curent
        and EDX, 01h ; in EDX ramane ultima cifra a lui EAX
        cmp EDX, 0 ; daca e zero, trecem mai departe cu cautarea
        jz diferit_de_1
        add EBX, 1 ; daca e 1, incrementam EBX iar rezultatul final e in EBX
        
        diferit_de_1:
        shr EAX, 1 ; trecem la cifra urmatoare
        cmp EAX, 0
        
        jnz repeta
        
        ; mov [ESP+8], EBX
        mov eax, ebx
        
        ret 4*2 ; eliberam argumentul de pe stiva