bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit, fscanf, printf, fopen               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    nf db 'fisier2.txt', 0
    ma db 'r', 0
    descriptor dd 0
    litera dd 0
    format db '%c', 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword ma
        push dword nf
        call [fopen]
        add ESP, 4*2
        cmp EAX, 0
        jz eroare_deschidere
        mov [descriptor], EAX
        
        repeta:
        
        push dword litera
        push dword format
        push dword [descriptor]
        call [fscanf]
        add ESP, 4*3
        cmp EAX, -1
        jz gata_citire
        
        cmp dword[litera], ' '
        jz nu_e_litera
        
        cmp dword[litera], 'a'
        jz litera_a
        cmp dword[litera], 'A'
        jz litera_a
        
        cmp dword[litera], 'b'
        jz litera_b
        cmp dword[litera], 'B'
        jz litera_b
        
        sub dword[litera], 2
        jmp gata_modificarea
        
        litera_a:
        mov dword[litera], 'y'
        
        litera_b:
        mov dword[litera], 'z'
        
        nu_e_litera:
        gata_modificarea:
        push dword [litera]
        push dword format
        call [printf]
        add ESP, 4*2
        
        jmp repeta
        gata_citire:
        
        eroare_deschidere:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
