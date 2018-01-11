#include <stdio.h>
#include <string.h>

void main(void)
 {
   char buffer[64] = "Jamsa\'s C/C++ Programmer\'s Bible";
   char target[64];

   int length;

   length = strxfrm(target, buffer, sizeof(buffer));

   printf("Length %d Target %s Buffer %s\n", length,
     target, buffer);
 }

