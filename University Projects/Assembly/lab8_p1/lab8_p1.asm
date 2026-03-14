bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dd 0 ; a-dword
    b dd 0 ; b-word
    format_c db '%d', 0
    format_a db "%d mod %d = %d", 0
    r dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword a
        push dword format_c
        call [scanf] ; citim a
        push dword b
        push dword format_c
        call [scanf] ; citim b
        add ESP, 4*4 ; eliberam stiva
        mov EAX, [a]
        CDQ          ; punem a pe EDX:EAX pt a putea folosi idiv
        mov EBX, [b]
        idiv EBX     ; EDX <- a%b
        mov dword[r], EDX ; punem in r restul
        push dword[r]
        push dword[b]
        push dword[a] 
        push dword format_a ; punem argumentele lui printf pe stiva
        call [printf]
        add ESP, 4*4 ; eliberam stiva
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
