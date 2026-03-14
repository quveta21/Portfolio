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
    a db 10
    b dw 7
    c dd 50
    d dq 15

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;c-(d+d+d)+(a-b)
        mov EDX, 0
        mov EAX, [c] ; c - qword
        sub EAX, [d]
        sbb EDX, [d+4]
        sub EAX, [d]
        sbb EDX, [d+4]
        sub EAX, [d]
        sbb EDX, [d+4] ; c - (d+d+d)
        mov EBX, 0
        mov BL, [a] ; a -> word
        sub BX, [b] ; (a-b)
        mov ECX, 0
        add EAX, EBX
        adc EDX, ECX ; c-(d+d+d)+(a-b)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
