bits 32

global _base2_to_integer

segment code use32 class = code

_base2_to_integer:
    push ecx
    push ebp
    
    mov ebp, esp
    
    push esi
    
    mov ecx, dword [ebp + 4 * 3]
    jecxz .invalid
    
    mov edx, 0
   
    mov ecx, dword [ebp + 4 * 3]
    
    mov esi, dword [ebp + 4 * 4]
    cld
    
    .iterate:
        lodsb
        sub al, '0'
        
        cmp al, 0
        jb .invalid
        cmp al, 1
        ja .invalid
        
        cmp al, 1
        jnz .zero
        dec ecx
        bts edx, ecx
        inc ecx
        ;add edi, edx
        
        .zero:
        
    loop .iterate
    
    jmp .valid
    
    .invalid:
        mov edx, 0
    
    .valid:
    
    mov eax, edx
    
    pop esi
    pop ebp
    pop ecx
    
    ret