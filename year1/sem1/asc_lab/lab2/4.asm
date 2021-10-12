bits 32 

global start        


extern exit              
import exit msvcrt.dll


segment data use32 class=data
    a db 7
    b db 4
    c db 3
    d dw 120

segment code use32 class=code
    start:
        ; (d - b * c + b * 2) / a
        
        mov bx, word [d]
        
        mov al, byte [b]
        mul byte [c]
        sub bx, ax
        
        mov al, byte [b]
        mov cl, 2
        mul cl
        add bx, ax
        
        mov ax, bx
        div byte [a]
        
    
        ; exit(0)
        push    dword 0    
        call    [exit]      
