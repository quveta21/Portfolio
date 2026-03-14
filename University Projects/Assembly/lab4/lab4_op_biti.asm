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
    a dw 0100101101101001b
    b dw 1011011111010001b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov bx, [c]
        mov cx, [c+2] ; cx:bx = c   
        mov bl, 11111b ; bitii 0-4 au val 1
        mov eax, 0
        mov ax, [a]
        and ax, 1111111b ; izolam bitii 0-6 ai lui a
        shl ax, 5 ; bitii 0-6 ai lui a pe pozitiile 5-11
        or bx, ax ; bitii 5-11 ai lui c    
        mov eax, 0
        mov ax, [b]
        and ax, 111100000000b ; izolam bitii 8-11 ai lui b
        shl ax, 4 ; bitii 8-11 ai lui b pe pozitiile 12-15
        or bx, ax
        mov cx, 0000000001100101b ; bitii 16-31 ai lui c
        push cx
        push bx
        pop ebx ; in ebx avem dublucuvantul c cerut
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
