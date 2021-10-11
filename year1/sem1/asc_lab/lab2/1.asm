bits 32 

global start        


extern exit         
import exit msvcrt.dll    

segment data use32 class=data
    ; ...

segment code use32 class=code
    start:
        ; -2 * 5
        
        mov al, -2
        mov bl, 5
        imul bl
    
        push    dword 0   
        call    [exit] 
