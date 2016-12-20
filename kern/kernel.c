
/*
int     32bits
short   16bits
char    8bits

*/

unsigned short * textmemptr;
unsigned short attrib = 0x0F;
int csr_x = 0, csr_y = 0;

void
putch(
		unsigned char c
	 ) {
	unsigned short *where;
	unsigned short att = attrib << 8;

		where = textmemptr + (csr_y * 80 + csr_x);
		*where = c | att;
		csr_x++;
}

/*

<15--background--12|11-----foreground----8|7--------charachter-------0>

*/
void
settextcolor(
		unsigned char forecolor,
		unsigned char backcolor
		) {
	attrib = (backcolor << 4) | (forecolor & 0x0F);
}



void kmain(){

	textmemptr = (unsigned short *)0xB8000;
	settextcolor(4, 0);
	csr_x =20;
	csr_y = 20;
	putch('H');
	putch('e');
	putch('L');
	putch('L');
	putch('o');
	for(;;);
}
