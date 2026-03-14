bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, prefix               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data public
    ; ...
    s1 db 'abcjane', 0
    l1 equ $-s1-1
    s2 db 'abcdef', 0
    l2 equ $-s2-1
    s3 db 'ablaosk', 0
    l3 equ $-s3-1
    p1 times l1+l2+1 db 0 ; prefixul pt s1 s2
    p2 times l2+l3+1 db 0 ; prefixul pt s2 s3
    p3 times l1+l3+1 db 0 ; prefixul pt s1 s3
    format db 'Prefixul comun pentru %s si %s este %s', 10, 0

; our code starts here
segment code use32 class=code public
    start:
        ; ...
        push dword l2 ; ESP + 20
        push dword s2 ; ESP + 16
        push dword l1 ; ESP + 12
        push dword s1 ; ESP + 8
        push dword p1 ; ESP + 4
        call prefix ; gaseste prefixul comun pt s1 s2
        
        push dword l3
        push dword s3
        push dword l2
        push dword s2
        push dword p2
        call prefix ; gaseste prefixul comun pt s2 s3
        
        push dword l3
        push dword s3
        push dword l1
        push dword s1
        push dword p3
        call prefix ; gaseste prefixul comun pt s1 s3
        
        push dword p1
        push dword s2
        push dword s1
        push dword format
        call [printf] ; afiseaza prefixul pt s1 s2
        add ESP, 4*4
        
        push dword p2
        push dword s3
        push dword s2
        push dword format
        call [printf]
        add ESP, 4*4 ; afiseaza prefixul pt s2 s3
        
        push dword p3
        push dword s3
        push dword s1
        push dword format
        call [printf]
        add ESP, 4*4 ; afiseaza prefixul pt s1 s3
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
