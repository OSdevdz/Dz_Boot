extern _start
BITS 16


jmp main

%include "gdt.inc"
%include "functions.asm"
main:

	cli				; clear interrupts
	xor	ax, ax			; null segments
	mov	ds, ax
	mov	es, ax
	mov	ax, 0x9000		; stack begins at 0x9000-0xffff
	mov	ss, ax
	mov	sp, 0xFFFF
	sti		
	
	call Enable_A20			; Just Confirm that A20 is enabled
					; to test on a Real PC.

	call GDT_install
	

	cli				; clear interrupts
	
	xor 	eax, eax				
	mov	eax, cr0		; set bit 0 in cr0--enter pmode
	or	eax, 0x00000001
	mov	cr0, eax
 	

	
	jmp	0x08:Protected_mode  ; CS:EIP; 0x08 = 0000 0000 0000 1000b	


	
bits 32
%include "Screen.inc"

Protected_mode:
	
	mov ax, 0x10   ;  Data Selector = 0x10 
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov esp, 0x90000

	call clear_screen
	call  _start  ; Call the entry of C_satge2.c 
	cli
	hlt





