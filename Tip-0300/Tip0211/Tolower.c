#include <stdio.h>
#include <ctype.h>

void main(void)
 {
   char string[] = "Jamsa\'s C/C++ Programmer\'s Bible";
   int i;

   for (i = 0; string[i]; i++)
     putchar(tolower(string[i]));
   putchar('\n');

   for (i = 0; string[i]; i++)
     putchar(_tolower(string[i]));
   putchar('\n');
 }
