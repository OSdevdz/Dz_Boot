ASM=yasm
ASMFLAGS=-f elf
GCC=gcc
GCCFLAGS=-c -I ./include -Wall -Wextra -ffreestanding -nostdlib \
	-nostartfiles -nodefaultlibs -m32 -g
LD=ld
LDFLAGS=-T kernel.ld
OBJ = loader.o kernel.o

all:  $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o kernel

%.o: %.c
	@$(GCC) $(GCCFLAGS) -o $@ $<       #the "@" before the command just to hide the Display of the command.

loader.o:
	@$(ASM) $(ASMFLAGS) loader.s -o loader.o  #the "@" before the command just to hide the Display of the command.


clean:
	rm -f *.o 

.PHONY: all clean run debug
