bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 db 1,3,5,7
    s2 db 2,6,9,4
    ls equ $-s2
    d times ls*2 db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ESI, 0 ; indexam cu 0 pt a folosi [s1+ESI] si [s2+ESI]
        mov EDI, d ; adresa sirului destinatie
        mov ECX, ls ; lungimea sirurilor parcurse
        jecxz final ; jump la sfarsit daca lungimea sirurilor este 0
        repeta:
            mov AL, [s1 + ESI] ; mutam in AL elementul din primul sir
            mov AH, [s2 + ESI] ; mutam in AH elementul respectiv din al doilea sir
            mov [EDI], AL ; punem in sirul destinatie s1[esi]
            mov [EDI+1], AH ; punem in sirul destinatie s2[esi]
            inc ESI ; trecem la urmatoarea pozitie din s1 si s2
            add EDI, 2 ; incrementam sirul destinatie cu 2 deoarece adaugam 2 elemente la un pas 
        loop repeta
        final:
            ; exit(0)
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
