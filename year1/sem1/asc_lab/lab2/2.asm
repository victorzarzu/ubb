bits 32


global start        

extern exit               
import exit msvcrt.dll    
                          
segment data use32 class=data
    ; ...
    a db 10
    b db 17
    c db 6
    d db 12

segment code use32 class=code
    start:
        ; (a + d - c) - (b + b)
        
        mov al, byte [a]
        add al, byte [d]
        sub al, byte [c]
        
        mov bl, byte [b]
        add bl, byte [b]
        
        sub al, bl
    
        ; exit(0)
        push    dword 0  
        call    [exit]   
