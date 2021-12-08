bits 32

global start

extern exit, scanf, printf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

%include  "base2_to_integer.asm"

segment data use32 class = data
    number resd 1
    format_integer db "%d", 0
    base2_number resb 33
    read_format_base2 db "%s", 0

segment code use32 class = code
    start:
        push number
        push format_integer
        call [scanf]
        add esp, 8
        
        cmp dword [number], 0
        jle invalid_number
        
        mov ecx, dword [number]
        
        iterate:
            push ecx
            
            push base2_number
            push read_format_base2
            call [scanf]
            add esp, 8
            
            mov edx, 0
            mov esi, base2_number
            cld
            
            number_label:
                lodsb
                cmp al, 0
                jz end_number
                inc edx
                jmp number_label
                
            end_number:
            mov eax, edx
            
            cmp eax, 0
            jz invalid_number
            
            push base2_number
            push eax
            call base2_to_integer
            add esp, 8
            
            push eax
            push format_integer
            call [printf]
            add esp, 8
            
            pop ecx
            
        loop iterate
        
        invalid_number:
    
        push 0
        call [exit]

