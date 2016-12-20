extern kmain


section .text

global loader
loader:
	mov esp, $kernel_stack
	push eax
	push ebx
	cli
	call kmain
	jmp $
	hlt


section .bss
	resb 2*1024*1024 ; 2MB of memory reserved
kernel_stack:
