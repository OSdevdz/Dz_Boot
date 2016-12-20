
int strlen(char *msg){
	int i = 0;
	while (msg[i] != 0) { i++;}
	return i;
}


void kprintf(char *msg) {

		unsigned short attr = 0x34 ;	
		unsigned short * textmemptr = (unsigned short *)0xB8000;
		unsigned int i = 0;
		for (i; i< strlen(msg); i++) {
		*(textmemptr+i) = ((attr << 8) | msg[i]) ;
			}

}
