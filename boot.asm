BITS 16
ORG 0x7c00


mov si, msg
call print


;---------------- We are Assuming that Qemu Enable A20 for Us ----------------
;otherwise We need to ckeck & try to enable A20 if it's not enabled yet.
; use Enable_A20 Function
; See the functions.asm file for more infos.

; Read Our Kernel from Disk to RAM
	call read_kernel


; Jump to execute Our stage2.bin
jmp 0x0:0x7e00

; Include Some Functions That We need
%include "functions.asm"

; Define a Message
msg db 13,"Hello World",10, 0


; We need to make some Padding With Zero
times 510 - ($-$$) db 0

; This Our Magic Boot Signature, Without that We are Useless for the BIOS :). 
dw 0xaa55

