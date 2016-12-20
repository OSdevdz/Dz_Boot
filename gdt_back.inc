%ifndef __gdt__inc
%define __gdt__inc
bits 16

GDT_install:
	cli
	pusha
	lgdt [gdtr_pointer]
	popa	
	sti
	ret


; We made a "FLAT MEMORY", Code & Data Are the same Sagment "from 0 to 4GB".
; Keep in mind that We need a GDT to switch to PM, So this One is just a Dummy One.
start_gdt:
	
;########################## START NULL DESCRIPTOR ###################################
	dd 0
	dd 0

;########################## END NULL DESCRIPTOR ###################################

;########################## START CODE DESCRIPTOR ###################################
	dw 0FFFFh     ; Limit 0-15 bits
	dw 0	      ; base address 0-15 bits
	db 0	      ; base middle 16-23 bits
	
	db 10011010b  ; ============================= TYPE + S + DPL + P ======================================
	; FROM RIGHT TO LEFT:
	; ~~~~~~~~~~~~~~~~~~
	
	; 1st bit	: 0 ---> Access bit, used with Virtual Memory (VM), We are not yet On VM, So it's 0
	

	; 2nd bit	: 1 ---> related to the 4th bit (Code/Data);1: R/X (Code) OR R/W (Data), 0: Execute Only (Code), Read Only (Data).   
	; 			the 4th bit is set .So, this mean "Code With Read + Execute".
	; 3rd bit 	: 0 ---> expansion direction, Ignore it. we Put 0.
	; 4th bit	: 1 ---> 1: Code segment / 0: Data Segment .See the 2nd bit too.
	; 5th bit	: 1 ---> 0 :System Descriptor / 1: Code Or Data Segment. the 4th bit is Set so it's a Code Seg.
	
		
	;NOTE:
	; The 2nd & 3rd & 4th bits make the "TYPE" field in the Descriptor. & 5th bit make the "S" field.

	; 6th&7th bits	: 00 --> Descriptor Privilege Level (DPL) : 00= Ring0 ; 11=Ring3. We are in Kernel Mode So, it's 00.
	; 8th bit	: 1 ---> Segment Present in memory (the P field), Used With VM. 1: is present / 0: No.
	;==================================================================================

	db 11001111b;================== FLAGS ================================================
	; FROM RIGHT TO LEFT:
	; ~~~~~~~~~~~~~~~~~~

	; 1st to 4th bits	: 1111 ---> Limit 16-19 bits.
	; 5th & 6th		: 00   ---> Reserved for OS.
	; 7th			: 1    ---> Segment type : 16/32 bits. 1: 32bits / 0 : 16 bits
	; 8th 			: 1    ---> Granularity  : 1: Limit x 4KB / 0: Limit x 1 byte. ==> in our case So Limit = 1Mega x 4KB = 4GB 
	;==================================================================================	
	db 0 ; Base Address 24-32 bits
;########################## END CODE DESCRIPTOR ###################################


;########################## START DATA DESCRIPTOR ###################################
	dw 0FFFFh
	dw 0
	db 0
	db 10010010b    ; The only diffrence With the Code Seg is the 4th bit; Here is 0 : DATA Segment.
	db 11001111b
	db 0
;########################## END CODE DESCRIPTOR ###################################
end_gdt:


gdtr_pointer:
	dw end_gdt - start_gdt - 1
	dd start_gdt

%endif
