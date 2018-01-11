#include <stdio.h>

void main(void)
 {
   int *iptr;      // Declare pointer variable
   int count = 1;

   iptr = &count;
   printf("Value of iptr %x Value of count %d Address of count %x\n", 
     iptr, count, &count);
 }
