bits 32

global start

extern exit, printf, scanf

import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class = data
    a resb 1
    b resw 1
    read_format db "%hhd %hd", 0
    print_format db "%d %d", 0
    da_text db "DA", 0
    nu_text db "NU", 0

segment code use32 class = code
    start:
        push b
        push a
        push read_format
        call [scanf]
        add esp, 4 * 3
        
        mov ecx, 16
        verify:
            push ecx
            mov cl, byte [a]
            mov al, byte [b]
            
            and al, cl
            cmp al, byte [a]
            
            jnz not_match
            
            push da_text
            call [printf]
            add esp, 4
            
            push dword 0
            call [exit]
            
            not_match:
            shr dword [b], 1
            
            pop ecx
        loop verify
        
        push nu_text
        call [printf]
        add esp, 4
        
        push dword 0
        call [exit]