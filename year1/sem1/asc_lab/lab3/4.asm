bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class = data
	a db 15
	b db 4
	c dw -7
	e dd -9872999
	x dq 14351

segment code use32 class = code
	;(a - b + c * 128) / (a + b) + e - x
	start:
		mov al, byte [a]
		sub al, byte [b]
		cbw
		mov bx, ax
		
		mov ax, word [c]
		mov cx, 128
		imul cx
		add ax, bx
		adc dx, 0
		
		push ax
		mov al, byte [a]
		add al, byte [b]
		cbw
		mov cx, ax
		pop ax
		idiv cx
		
		cwde
		cdq
		add eax, dword [e]
    adc edx, 0

		sub eax, dword [x]
		sbb edx, dword [x + 4]
		
		push dword 0
		call [exit]
