#include <stdio.h>
#include <string.h>

void main(void)
 {
   char title[64] = "Jamsa\'s C/C++ Programmer\'s Bible!";
   char *ptr;

   if (ptr = strrchr(title, 'C'))
     printf("Rightmost occurrence of C is at offset %d\n",
       ptr - title);
   else
     printf("Character not found\n");
 }
