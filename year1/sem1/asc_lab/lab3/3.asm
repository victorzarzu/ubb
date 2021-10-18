bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
	a db 15
	b db 4
	c dw 100
	e dd 9872
	x dq 4124

segment code use32 class = code
	;(a - b + c * 128) / (a + b) + e - x
	start:
		mov bl, byte [a]
		sub bl, byte [b]
		
		mov ax, word [c]
		mov cx, 128
		mul cx
		
		mov bh, 0
		add ax, bx
		adc dx, 0
		
		mov cx, 0
		mov cl, byte [a]
		add cl, byte [b]
		adc ch, 0
		div cx
		
		push ax
		mov eax, 0
		pop ax
		mov edx, 0
		add eax, dword [e]
		adc edx, 0
		sub eax, dword [x]
		sbb edx, dword [x + 4]
		
		push dword 0
		call [exit]