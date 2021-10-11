bits 32

global start       

extern exit               
import exit msvcrt.dll            


segment data use32 class=data
    SYS_write equ 1
    STDOUT equ 1
    
    str_num resb 20
    
    a db 13
    d db 6
    e dw 11
    f dw 23


segment code use32 class=code
    
    
    start:
        ; (a * d * e) / (f - 5)
        
        mov al, byte [a]
        mov bl, byte [d]
        imul bl
        
        mov bx, word [e]
        mul bx
        
        mov bx, word [f]
        sub bx, 5
        idiv bx
        
		mov di, ax
		;call num_to_string
        
        ;mov eax, SYS_write
        ;mov edi, STDOUT
        ;mov esi, str_num
        ;mov edx, ecx
        ;syscall

    
        ; exit(0)
        push    dword 0      
        call    [exit]       
		
	num_to_string:

        mov si, 0
        cmp di, 0
        jge not_negative
        mov si, 1
        neg di
        not_negative:
        
        mov cx, 1
        num_to_string:
            mov ax, di
            cwd
            mov bx, 10
            div bx
            mov di, ax
            add dx, '0'
            push dx
            inc cx
            cmp di, 0
            jne num_to_string
            
        
        mov byte [str_num], '+'
        cmp si, 0
        je not_neg 
        mov byte [str_num], '-'
        not_neg:
        
        mov si, 1
        mov edx, str_num
        inc edx
        
        popping:
            pop ax
            mov byte [edx], al
            inc edx
            inc si
            cmp si, cx
            jne popping
            
        mov byte [edx], 0

		ret