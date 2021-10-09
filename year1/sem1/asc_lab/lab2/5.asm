bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start       
;global print_num

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    SYS_write equ 1
    STDOUT equ 1
    
    str_num resb 20
    
    a db 13
    d db 6
    e dw 11
    f dw 23

; our code starts here
segment code use32 class=code
    ;global print_num
    
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
        
        mov eax, SYS_write
        mov edi, STDOUT
        mov esi, str_num
        mov edx, ecx
        syscall

    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
