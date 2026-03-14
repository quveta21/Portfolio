; Se da numele unui fisier. Acesta contine cifre separate prin spatiu (baza 16). Sa se afiseze
; fiecare cifra citita din fisier si nr de biti 1 din reprezentarea binara a acesteia.


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fscanf, printf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data public
    ; ...
    nf db 'fisier1.txt', 0
    ma db 'r', 0
    descriptor dd 0
    cifra dd 0
    frecventa dd 0
    format db '%x', 0
    format_afisare db '%x - %d', 10, 0
    

; our code starts here
segment code use32 class=code public
    start:
        ; ...
        push dword ma
        push dword nf
        call [fopen]
        add ESP, 4*2
        cmp EAX, 0
        jz eroare_deschidere
        mov [descriptor], EAX
      
        citire_repeta:  
        push dword cifra
        push dword format
        push dword [descriptor]
        call [fscanf]
        add ESP, 4*3
        cmp EAX, -1
        jz gata_citire
        
        ; push dword 0
        ; push dword cifra
        ; call nr_biti_1
        
        nr_biti_1:
        mov EAX, [cifra] ; in EAX retinem numarul
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
        
        push dword ebx
        push dword [cifra]
        push dword format_afisare
        call [printf]
        add ESP, 4*3
        
        jmp citire_repeta
        gata_citire:
        
        
        ; exit(0)
        eroare_deschidere:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
