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
    s dd 12345678h, 1A2B3C4Dh, 0FE98DC76h
    ls equ ($-s)/4
    d times ls db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, ls ; lungimea sirului parcurs
        jecxz final ; daca sirul nu are elemente
        CLD ; directia de parcurgere de la st la dr
        mov ESI, s ; adresa sirului sursa
        mov EDI, d ; adresa sirului destinatie
        repeta:
            LODSD ; EAX primeste dublucuvantul din s
            shr EAX, 24 ; in AL avem octetul superior din cuvantul superior din elementul din s
            mov BL, AL ; retinem aceasta valoare in BL pt a putea modifica AL
            mov BH, 3
            div BH ; impartim valoarea la 3
            CMP AH, 0 ; verificam daca restul impartirii a fost 0
            JNE urmatorul ; in caz contrar, se sare peste adaugarea lui in sirul d
            mov AL, BL
            STOSB ; adaugam octetul divizibil cu 3 in sirul d
            urmatorul:
        loop repeta
        final:
            ; exit(0)
            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program
