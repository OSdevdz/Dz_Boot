/* AtlantisOS source file - /src/boot/elf.h
 *
 * This file contains the ELF defines and structures. It also contains the
 * functions in the setup portion for loading elf files.
 *
 * Todo list:
 *   xx-xx-xxxx xx:xx xxxxx - support nmagic & omagic elfs
 *   xx-xx-xxxx xx:xx xxxxx - support 64-bit loading
 *
 * Revision history:
 *   31-10-2003 10:45 candy - separating the ELF code from the floppy files
 *   31-10-2003 08:35 candy - Creation of this file and the revision history
 */

#ifndef ELF_H
#define ELF_H

typedef unsigned short int Elf32_Half;
typedef unsigned int Elf32_Word;
typedef void (*Elf32_Entry_Point)(void);
typedef char *Elf32_Addr;
typedef unsigned int Elf32_Off;

typedef struct {
	unsigned char e_ident[16];
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Entry_Point e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
}elf_header ;

typedef struct {
	Elf32_Word p_type;
	Elf32_Off p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_memsz;
	Elf32_Word p_flags;
	Elf32_Word p_align;
}elf_program_table;

typedef elf_program_table Elf_Phdr;
typedef elf_header        Elf_Ehdr; 
void elf_check(Elf_Ehdr *head);

#endif

