#include <stdio.h>

void main(void)
 {
   int result;

   result = printf("Jamsa\'s C/C++ Programmer\'s Bible!\n");
   if (result == EOF)
     fprintf(stderr, "Error within printf\n");
 }
