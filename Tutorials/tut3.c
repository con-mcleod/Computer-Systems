//Q8

#define ASCII 0x80
#define MASK2 0xC0
#define MASK3 0xE0
#define MASK4 0xF0
#define TOP4 0xF0

int unicodeNsymbols(unsigned char *str) {
	int numSymbols = 0;
	uchar *c = str;
	while (*c != '\0') {
		if ((*c & ASCII) == 0) {
			c++;
		} else if ((*c & TOP4) == MASK2) {
			c+=2;
		} else if ((*c & TOP4) == MASK3) {
			c+=3;
		} else if ((*c & TOP4) == MASK4) {
			c+=4;
		}
		ns++;
	}
	return ns;
}