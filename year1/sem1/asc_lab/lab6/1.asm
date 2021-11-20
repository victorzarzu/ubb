bits 32

global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data
	S dd 12345607h, 1A2B3C15h, 00BC6712h, 12121212h
	len equ ($ - S)
	d resb len
    mesaj db "%d "

segment code use32 class = code
start:

	mov ecx, len
	mov edi, d
	mov esi, S
	
	jecxz not_dim
    cld
    
	move:
		movsb
	loop move
	
	not_dim:
	

	mov ecx, len
	cmp ecx, 0
	je not_dimension
    cld
    
	iterate:
		mov ecx, 0
		mov ebx, 0
		mov esi, d
		
		sort:
            cld
            lodsb
            mov edi, esi
            push esi
            push esi
            
            scasb
            
            jbe is_ok
            
            pop edi
            mov esi, edi
            std
            lodsb
            movsb
            cld
            stosb
            mov ebx, 1
            
            is_ok:
            cmp ebx, 1
            jz changed
            add esp, 4
            changed:
            
            pop esi
            inc ecx
            cmp ecx, len - 1
        
        jne sort
           
		
		cmp ebx, 1
	jz iterate
	
	not_dimension:

	push dword [0]
	call [exit]