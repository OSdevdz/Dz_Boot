
#include "elf.h"
#include "stdlib.h"

void elf_check(Elf_Ehdr *head) {
	if (head->e_ident[0] != '\x7F' || head->e_ident[1] != 'E' ||
	    head->e_ident[2] != 'L' || head->e_ident[3] != 'F') {
		kprintf("File is not ELF.");
		__asm__ __volatile__("hlt");  // We can just make "return;" and the stage2 will hlt. But I prefer to Halt here.		
	}
	if (head->e_ident[4] != 1) {
		kprintf("File is not 32-bit.");
		__asm__ __volatile__("hlt"); // Elli Yasra Hena Yabka Hena :).
	}
	if (head->e_ident[5] != 1) {
		kprintf("File is not little-endian.");
		__asm__ __volatile__("hlt"); // Elli Yasra Hena Yabka Hena :).
	}
	if (head->e_ident[6] != 1) {
		kprintf("File is not ELF version 1.");
		__asm__ __volatile__("hlt"); // Elli Yasra Hena Yabka Hena :).
	}
	if (head->e_type != 2) {
		kprintf("File is not executable.");
		__asm__ __volatile__("hlt");
	}
	if (head->e_machine != 3) {
		kprintf("File is not for 386+ systems.");
		__asm__ __volatile__("hlt");
	}
	if (head->e_version != 1) {
		kprintf("File is not ELF version 1.");
		__asm__ __volatile__("hlt");
	}
	if ((unsigned int)head->e_entry < (unsigned int)0x100000) {
		kprintf("Entry point outside of kernel.");
		__asm__ __volatile__("hlt");
	}
	if (head->e_phoff > 0x80000) {
		kprintf("Program header outside of kernel image.");
		__asm__ __volatile__("hlt");
	}
	if (head->e_phnum < 1) {
		kprintf("No program headers.");
		__asm__ __volatile__("hlt");
	}
	if (head->e_phentsize < 0x20) {
		kprintf("program headers Noncompliant.");
		__asm__ __volatile__("hlt");
	}
}

