bits 32

global start

extern exit, scanf, printf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data
    a resd 1
    b resd 1
    read_format db "%x %x", 0
    print_format db "%lld", 0

segment code use32 class = code
    start:
        
        push b
        push a
        push read_format
        call [scanf]
        add esp, 4 * 3
        
        mov edx, 0
        mov eax, dword [a]
        add eax, dword [b]
        adc edx, 0
        
        push edx
        push eax
        push print_format
        call [printf]
        add esp, 4 * 3
        
        push dword 0
        call [exit]