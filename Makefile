#CCFLAGS = -g -std=gnu99 -nostdinc -static -fno-omit-frame-pointer -Wall -Wno-format -Wno-unused -Werror -fno-stack-protector \
#	-fno-builtin -ffreestanding  \
#       -nostdinc -nostartfiles \
#	-nodefaultlibs -nostdlib \

CCFLAGS = -std=gnu99 -fno-hosted -fno-omit-frame-pointer -fno-stack-protector \
		-Wall -Wno-format -Wno-unused -Werror
	  

	
OBJ = stage2.o c_stage2.o kprintf.o elf.o

all: new_disk mbr.bin stage2.bin write


new_disk:
	dd if=/dev/zero of=disk.img bs=512 count=2880
mbr.bin: boot.asm
	nasm -f bin boot.asm -o mbr.bin

stage2.bin: $(OBJ)
	ld -o stage2.bin $(OBJ) --oformat binary -Ttext 0x7e00 -e _start
	
stage2.o:
	nasm -f elf stage2.asm -o stage2.o
%.o:%.c
	gcc $(CCFLAGS) $< -c -o $@             
	objcopy --remove-section .comment $@
	objcopy --remove-section .eh_frame $@
	objcopy --remove-section .note.GNU-stack $@
write:
	dd if=mbr.bin of=disk.img seek=0 count=1 bs=512 conv=notrunc
	dd if=stage2.bin  of=disk.img seek=1 count=5 bs=512 conv=notrunc
	dd if=kern/kernel  of=disk.img seek=6 count=50 bs=512 conv=notrunc
run:
	qemu-system-i386 -hda disk.img

debug:
	qemu-system-i386 -s -S -hda disk.img

clean:
	rm -f *.bin *.o *.img
