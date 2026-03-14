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
    a db 102
    b db 20
    c dw 30 
    e dd 1000
    x dq 800

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;(a-2)/(b+c)+a*c+e-x
        mov AL, [a]
        sub AL, 2
        mov AH, 0
        mov DX, 0 ; DX:AX <- (a-2)
        mov BX, [c]
        add BL, [b] ; BX <- (b+c)
        div BX ; AX <- (a-2)/(b+c)
        mov CX, AX
        mov AL, [a]
        mov AH, 0
        mov DX, 0 ; DX:AX <- a
        mul WORD[c] ; DX:AX <- a*c
        add AX, CX
        adc DX, 0; DX:AX <- a*c + (a-2)/(b+c)
        mov ECX, 0
        mov CX, AX ; mutam suma obtinuta pana acum pe word
        mov EAX, [e]
        mov EDX, 0
        sub EAX, [x]
        sbb EDX, [x+4]; EDX:EAX <- e-x
        add EAX, ECX ; suma finala
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
