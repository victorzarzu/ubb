bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
	S dd 12345607h, 1A2B3C15h
	len equ ($ - S) / 4
	d resb len * 4

segment code use32 class = code
start:

	mov ecx, len * 4
	mov edi, d
	mov esi, S
	
	jecxz not_dim
	move:
		movsb
	loop move
	
	not_dim:
	
	mov ecx, len
	cmp ecx, 0
	je not_dimension
	iterate:
		mov ecx, 0
		mov ebx, 0
		mov esi, d
		
		sort:
			mov dl, [esi]
			cmp dl, [esi + 1]
			jb is_ok
			mov al, [esi + 1]
			mov [esi], al
			mov [esi + 1], dl
			mov ebx, 1
			is_ok:
		
			inc esi
			inc ecx
			cmp ecx, len * 4 - 1
		jne sort
		
		cmp ebx, 1
	je iterate
	
	not_dimension:

	push dword [0]
	call [exit]