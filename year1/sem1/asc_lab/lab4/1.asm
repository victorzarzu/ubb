bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
	a dd 0xaa000fcea
	n resb 1
	b resd 1
	c resb 1

segment code use32 class = code
	;Se da dublucuvantul A. Sa se obtina numarul intreg n reprezentat de bitii 14-17 ai lui A. Sa se obtina apoi in B dublucuvantul rezultat prin rotirea spre stanga a lui A cu n pozitii. Sa se obtina apoi octet C astfel:
	;bitii 0-5 ai lui C coincid cu bitii 1-6 ai lui B
	;bitii 6-7 ai lui C coincid cu bitii 17-18 ai lui B
	start:
		
		mov eax, dword [a]
		shr eax, 14
		and eax, 00001111b
		mov byte [n], al
		
		mov eax, dword [a]
		mov cl, byte [n]
		rol eax, cl
		mov dword [b], eax
		
		mov eax, dword [b]
		shr eax, 1
		and al, 00111111b
		mov byte [c], al
		shr eax, 10
		and al, 11000000b
		or byte [c], al
		
		push dword 0
		call [exit]