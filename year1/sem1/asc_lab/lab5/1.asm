bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
	S db 1, 3, -2, -5, 3, -8, 5, 0
	len equ $ - S
	D1 resb len
	D2 resb len
	
segment code use32 class = code
	;Se da un sir de octeti S. Sa se construiasca un sir D1 care sa contina toate numerele pozitive si un sir 
	;D2 care sa contina toate numerele negative din S.
	start:
		;mov ecx, len
		;mov esi, S
		;mov edx, 0
		
		;jecxz len_zero
		;iterate:
		;	cmp byte [esi], 0
		;	jl negative
		;	inc edx
		;	negative:
			
		;	inc esi
		;	dec ecx
		;	cmp ecx, 0
		;	jne iterate
		;len_zero:
		
		;jmp declarations
		;d1_len equ 0
		;%define d1_len edx
		;D1 times edx db 0
		;D2 resb (len - edx)
		;declarations:
		
		mov esi, S
		mov ecx, len
		mov eax, D1
		mov ebx, D2
		
		jecxz empty
		create:
			mov dl, byte [esi]
			
			cmp dl, 0
			jl negative
			mov [eax], dl
			inc eax
			jmp end_compare
			
			negative:
			mov [ebx], dl
			inc ebx
			end_compare:
		
			inc esi
			dec ecx
			cmp ecx, 0
			jne create
		empty:
		
		push dword 0
		call [exit]