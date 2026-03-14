bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fscanf, fopen, fclose, printf         ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    nf db 'f.txt', 0
    ma db 'r', 0
    descriptor dd 0
    format db '%c', 0
    format_frecv db 'Litera %c apare de %d ori', 0
    litera dd 0
    frecventa dd 0
    aparitii times 26 db 0
    err db 'Eroare...', 0

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
        
        cmp byte[litera], 'a'
        jb nu_e_lowercase
        cmp byte[litera], 'z'
        ja nu_e_lowercase
        mov EAX, 0
        mov AL, [litera]
        inc byte[aparitii + EAX - 'a']
        nu_e_lowercase:
        jmp repeta
        gata_citire:
        
        mov EAX, 0 ; frecventa maxima -> AL
        mov EBX, 0 ; litera de frecventa maxima -> BL
        mov EDI, aparitii
        mov ECX, 26
        cld
        loop_frecventa:
        scasb ; cmp AL, es:[EDI]
        ja nu_e_maxim
        mov AL, [EDI-1]
        mov EBX, EDI 
        nu_e_maxim:
        loop loop_frecventa
        
        sub EBX, aparitii+1
        add EBX, 'a'
        
        push EAX
        push EBX
        push dword format_frecv
        call [printf]
        add ESP, 4*3
        
        push dword[descriptor]
        call [fclose]
        add ESP, 4*1
        jmp final
        
        eroare_deschidere:
        push dword err
        call [printf]
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
