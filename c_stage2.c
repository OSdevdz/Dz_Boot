#include "elf.h"
#include "stdlib.h"

void (*entrypt)(void);   // entrypt();

Elf_Phdr *phdrs, *eph;
unsigned char *pa; 

//----------------- copy_kern() START -------------------
void copy_kern(char *dest, char *src, unsigned int len)
{
	//unsigned int len = *l;  
	for(; len != 0; len--) *dest++ = *src++;
}

//----------------- copy_kern() END ---------------------

 
// ---------------- memset() Start ---------------
void memset(char *dest, char val, unsigned int len)
{
  for ( ; len != 0; len--) *dest++ = val;
}
//---------------- memset END-----------------------------

void _start(){

/* I will Try To move the Kernel from 0x8800 to 0x200000 here*/


		copy_kern((char* )0x200000, (char *)0x8800, 16000); // move the kernel to 0x200000 / 15360 how much sectors the kernel occupys

		// this it will not work unless we link our Kernel to be > 0x200000. !!!!!!????

		Elf_Ehdr *ehdr = (Elf_Ehdr *)0x200000; // use an empty Address Space		

		elf_check(ehdr);
	
		kprintf("Hmmmmm, it is an ELF");

#if 1
//--------------------------------Load & Execute The ELF Kernel -------------------
	//unsigned char *src  = (unsigned char *) 0x200000;
	//unsigned char *dest = (unsigned char *) 0x100000;

	
	
	phdrs = (Elf_Phdr *)((char*)ehdr + ehdr->e_phoff);
  	
	int i;
	for (i = 0; i < ehdr->e_phnum; i++)
	{
		Elf_Phdr *phdr = (Elf_Phdr *) ((char *)phdrs + i * ehdr->e_phentsize);
		if (phdr->p_type == 1) // PT_LOAD = 1
		{		
		copy_kern(phdr->p_paddr,(char *)ehdr + phdr->p_offset, phdr->p_filesz );			
			if (phdr->p_filesz < phdr->p_memsz)
		           memset ((char *)phdr->p_paddr + phdr->p_filesz, 0, (phdr->p_memsz - phdr->p_filesz));
						                        
		}
	}

	
	ehdr->e_entry();
	entrypt();
	



//----------------------------- ENd ELF Loader---------------------------
#endif		
		while(1);
}

		


