read_kernel:
	mov ah, 0x02
	mov al, 0x38    ; the number of sectors is related to the size of stage2 + kern/kernel.
	mov ch, 0x0
	mov cl, 0x02
	mov dh, 0x0
	mov dl, 0x80
	xor bx, bx
	mov es, bx
	mov bx, 0x7e00
	int 13h
	jc read_kernel
	ret

; ################## Just Print Some Nice Messages ##############	
print:
	mov al, [si]
	cmp al, 0
	je done
	mov ah, 0x0e
	int 0x10
	add si, 1
	jmp print

done:
	ret


;########################## INT 15 ###################

; return Value in AL : 0 disabled, 1 enabled
;
checka20_int15:
	mov ax, 0x2402
	int 0x15
	ret

Disable_A20:

	mov ax, 0x2400
	int 0x15

	ret

Enable_A20:
	mov ax, 0x2401
	int 0x15
	ret
;########################## END INT 15###############



;############################## Another Portable Way to Check The A20 Line ###################### 
CheckA20:
    pushf
    push ds
    push es
    push di
    push si
 
    cli
 
    xor ax, ax ; ax = 0
    mov es, ax
 
    not ax ; ax = 0xFFFF
    mov ds, ax
 
    mov di, 0x0500
    mov si, 0x0510
 
    mov al, byte [es:di]
    push ax
 
    mov al, byte [ds:si]
    push ax
 
    mov byte [es:di], 0x00
    mov byte [ds:si], 0xFF
 
    cmp byte [es:di], 0xFF
 
    pop ax
    mov byte [ds:si], al
 
    pop ax
    mov byte [es:di], al
 
    mov ax, 0
    je check_a20__exit
 
    mov ax, 1
 
check_a20__exit:
    pop si
    pop di
    pop es
    pop ds
    popf
 
    ret  
