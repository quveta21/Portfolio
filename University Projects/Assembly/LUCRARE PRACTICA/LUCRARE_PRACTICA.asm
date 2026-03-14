bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, scanf, fprintf, fread               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import fread msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    nf times 50 db 0
    nf_output db 'output.txt', 0
    ma_input db 'r', 0
    ma_output db 'a', 0
    descriptor_input dd 0
    descriptor_output dd 0
    n dd 0
    format_sir db '%s', 0
    format_nr db '%d', 0
    format_cuvant_afisare db '%s ', 0
    text times 100 db 0
    cuvant times 100 db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword nf
        push dword format_sir
        call [scanf]
        add ESP, 4*2 ; citim numele fisierului
        
        push dword n
        push dword format_nr
        call [scanf]
        add ESP, 4*2 ; citim numarul n
        
        push dword ma_input
        push dword nf
        call [fopen]
        add ESP, 4*2
        cmp EAX, 0
        jz eroare_deschidere
        mov [descriptor_input], EAX ; deschidem fisierul si retinem descriptorul sau
        
        push dword ma_output
        push dword nf_output
        call [fopen]
        add ESP, 4*2
        cmp EAX, 0
        jz eroare_deschidere
        mov [descriptor_output], EAX
        
        push dword text
        push dword 1
        push dword 100
        push dword [descriptor_input]
        call [fread]
        add ESP, 4*4 ; citim in text tot continutul fisierului
        
        mov ESI, text
        mov EDI, cuvant ; retinem la fiecare pas cuvantul
        mov EAX, 0
        mov EBX, 0 ; vom retine numarul de caractere parcurse ale cuvantului curent
        cld
        repeta:
            lodsb ; AL <- [ESI] adica caracterul curent
            stosb ; [EDI] <- AL
            cmp AL, 'a'
            jb nu_e_litera
            
            cmp AL, 'z'
            ja nu_e_litera
            
            inc EBX
            cmp byte[ESI], 'a' ; dupa lodsb, ESI creste cu o pozitie deci ajunge la caracterul urmator.
                           ; verificam daca cuvantul continua sau s-a sfarsit si in EBX e numarul lui de caractere
            jb cuvantul_continua
            
            cmp byte[ESI], 'z'
            ja cuvantul_continua
            
            cmp EBX, [n]
            jne nu_are_lungimea_buna
            
            push dword cuvant
            push dword format_cuvant_afisare
            push dword [descriptor_output]
            call [fprintf]
            add ESP, 4*3
            
            mov EDI, cuvant ; resetam cuvantul
            
            nu_are_lungimea_buna:
            nu_e_litera:
            mov EBX, 0
            cuvantul_continua:
        jmp repeta
        eroare_deschidere:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

        
        ; fread(buffer=sir,size=1,count=100,descriptor)