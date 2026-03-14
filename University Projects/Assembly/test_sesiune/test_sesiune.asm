bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir dd -1, 123456, 0ABCDEFFh, 0ABCDEFFh, 0CBCDEFFh, 0DBCDEFFh, 0111010101b
    lungime_sir equ ($-sir)/4
    format_afisare db '%x ', 0
    sir_sume times lungime_sir db 0
    index dd 0
    spatiu db 13,10,0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ECX, lungime_sir
        CLD
        mov ESI, sir
        mov EDI, sir_sume
        repeta:
            mov BL, 0 ; aici calculam cifrelor suma fiecarui numar
            lodsd ; EAX <- numarul curent
            repeta_suma:
                mov EDX, EAX
                and EDX, 0Fh
                add BL, DL ; adunam ultima cifra binara
                shr EAX, 4
                cmp EAX, 0
            jnz repeta_suma
            mov AL, BL
            stosb
        loop repeta
        
        mov ESI, sir_sume + 1
        mov BL, [sir_sume] ; in bl avem suma anterioara
        mov ECX, lungime_sir - 1
        mov DL, 1 ; lungimea curenta
        CLD
        cauta:
            lodsb ; AL <- suma curenta
            cmp BL, AL
            jb urmator ; suma anterioara e mai mica
            cmp DL, 1
            je nu_e_secventa
            push ESI
            mov ESI, sir
            add ESI, [index]
            add ESI, [index]
            add ESI, [index]
            add ESI, [index]
            push EAX
            push EBX
            push ECX
            push EDX
            movzx ECX, DL
            repeta_afisare:
                lodsd
                push ECX
                push EAX
                push dword format_afisare
                call [printf]
                add ESP, 4*2
                pop ECX
            loop repeta_afisare
            push dword spatiu
            call [printf]
            add ESP, 4*1
            pop EDX
            pop ECX
            pop EBX
            pop EAX
            pop ESI
            mov DL, 0
            mov dword[index], lungime_sir
            sub dword[index], ECX
            urmator:
            inc DL
            jmp e_secventa
            nu_e_secventa:
            mov dword[index], lungime_sir
            sub dword[index], ECX
            e_secventa:
            mov BL, AL
        loop cauta
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
