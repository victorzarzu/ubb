bits 32

global start

extern exit, fopen, fprintf, fclose

import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class = data
    fisier db "date.txt", 0
    text db "$Astazi EstE o ZI foArte frumoASA!", 0
    mod_acces db "w", 0
    descriptor resd 1
    format db "%s", 0

segment code use32 class = code
    start:
    
        mov esi, text
        cld
        
        iterate:
            mov edi, esi
            lodsb
            
            cmp al, 'A'
            jb not_great
            cmp al, 'Z'
            ja not_great
            add al, 'a' - 'A'
            
            not_great:
            
            stosb
            cmp al, 0
            jnz iterate
        
        push mod_acces
        push fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        jz not_fisier
        
        mov dword [descriptor], eax
        
        push text
        push format
        push dword [descriptor]
        call [fprintf]
        add esp, 4 * 3
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        not_fisier:
        
        push dword 0
        call [exit]