#include <stdio.h>

void main(void)
 {
	#ifdef __STDC__
		printf("ANSI C compliance\n");
	#else
		printf("Not in ANSI C mode\n");
	#endif
 }
