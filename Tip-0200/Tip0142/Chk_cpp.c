#include <stdio.h>

void main(void)
 {
	#ifdef __cplusplus
		printf("Using C++\n");
	#else
		printf("Using C\n");
	#endif
 }
