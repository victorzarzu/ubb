bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
	a db 10
	b dw 124
	c dd 2453
	d dq 932523

segment code use32 class = code
	; a - d + b + b + c
	start:
		mov eax, 0
		mov al, byte [a]
		mov edx, 0
		
		sub eax, dword [d]
		sbb edx, dword [d + 4]
		
		mov ecx, 0
		mov cx, word [b]
		add eax, ecx
		adc edx, 0
		
		add eax, ecx
		adc edx, 0
		
		add eax, dword [c]
		adc edx, 0
		
	
	push dword 0
	call [exit]