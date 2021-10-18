bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
	a db 2
	b dw 3
	c dd 125
	d dq 156781
	
segment code use32 class = code
	; (d + d - b) + (c - a) + d
	start:
		push dword [d + 4]
		push dword [d]
		
		mov eax, dword [d]
		mov ebx, dword [d + 4]
		add dword [d], eax
		adc dword [d + 4], ebx
		
		mov eax, 0
		mov ax, word [b]
		sub dword [d], eax
		sbb dword [d + 4], 0
	
		mov ebx, 0
		mov bl, byte [a]
		sub dword [c], ebx
		
		mov ecx, dword [c]
		add dword [d], ecx
		adc dword [d + 4], 0
		
		pop eax
		pop ebx
		add dword [d], eax
		adc dword [d], ebx
		
	
	push dword 0
	call [exit]