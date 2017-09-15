#include <stdio.h>
#include <stdlib.h>
#include <string.h>


union _all {
   int   ival;
   char  cval;
   char  sval[4];
   float fval;
   unsigned int uval;
} u;





int main(int argc, char **argv)
{

	union _all u;
	u.uval = 0x00216948;
	printf("this is the one that matters: %s\n", u.sval);
	printf("%d\n", u.ival);
	printf("%c\n", u.cval);

	return 0;
}
 

