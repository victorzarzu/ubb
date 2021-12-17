bits 32

global base2_to_integer

segment code use32 class = code

base2_to_integer:
    push ebp
    mov ebp, esp
    
    push esi
    push edi
    push ebx
    
    mov ecx, dword [ebp + 4 * 2]
    jecxz .invalid
    
    mov esi, dword [ebp + 4 * 3]
    mov edi, dword [ebp + 4 * 4]

    mov eax, ecx
    mov edx, 0
    
    mov ebx, 3
    div ebx
    
    cmp edx, 0
    jnz .not_divisible
    
    mov edx, 3
    jmp .end_precompute
    
    .not_divisible:
    inc eax
    .end_precompute:
    push eax
    
    
    mov ebx, 2
    mov eax, 3
    sub eax, edx
    sub ebx, eax
    mov edx, 0
    
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
        bts edx, ebx
        
        .zero:
        
        dec ebx
        cmp ebx, 0
        jge .not_switch
        
            add edx, '0'
            mov al, dl
            
            stosb
            
            mov ebx, 2
            mov edx, 0
        
        .not_switch:
        
    loop .iterate
    
    jmp .valid
    
    .invalid:
        mov byte [edi], 0
        jmp .all
    
    .valid:
    
    pop ecx
    mov edi, dword [ebp + 4 * 4]
    mov byte [edi + ecx], 0
    mov eax, edi
    
    .all:
    
    pop ebx
    pop edi
    pop esi
    pop ebp
    
    ret