bits 32 

global start        

extern exit       
import exit msvcrt.dll   

segment data use32 class=data
    ; ...
    a dw 156
    b dw 300
    c dw 12
    d dw 500


segment code use32 class=code
    start:
        ; (c + d) + (a - b) + a
        
        mov ax, word [c]
        add ax, word [d]
        
        mov bx, word [a]
        sub bx, word [b]
        
        add ax, bx
        add ax, word [a]
        
        
        push    dword 0
        call    [exit]  
