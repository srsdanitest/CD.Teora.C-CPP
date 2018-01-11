#include <stdio.h>
#include <dir.h>

void main(void)
 {
   printf("The current drive is %c\n", getdisk() + 'A');
 }
