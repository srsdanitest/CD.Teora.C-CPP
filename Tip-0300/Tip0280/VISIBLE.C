#include <stdio.h>

void main(void)
 { 
   int value = 1500;

   if (value > 1499)
     {
       int value = 1;

       printf("Inner value is %d\n", value);
     }

   printf("Outer value is %d\n", value); 
 }
