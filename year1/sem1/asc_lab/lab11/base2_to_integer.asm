bits 32

global base2_to_integer

segment code use32 class = code

base2_to_integer:
    push ecx
    push ebp
    
    mov ebp, esp
    
    push esi
    push edi
    
    mov ecx, dword [ebp + 4 * 3]
    jecxz .invalid
    
    mov edi, 0
    mov edx, 1
    
    dec ecx
    .create_power:
        shl edx, 1
    loop .create_power
    
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
        add edi, edx
        
        .zero:
        
        shr edx, 1
        
    loop .iterate
    
    jmp .valid
    
    .invalid:
        mov edi, 0
    
    .valid:
    
    mov eax, edi
    
    pop edi
    pop esi
    pop ebp
    pop ecx
    
    ret