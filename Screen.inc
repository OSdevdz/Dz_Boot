%ifndef __Screen__inc
%define __Screen__inc

bits 32


clear_screen:

	pusha
	cld
	mov	edi, 0xB8000
	mov	cx, 2000
	mov	ah, 50
	mov	al, ' '	
	rep	stosw

	popa
	ret


%endif
