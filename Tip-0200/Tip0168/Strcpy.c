#include <stdio.h>
#include <string.h>

void main(void)
 {
   char title[] = "Jamsa\'s C/C++ Programmer\'s Bible";
   char book[128];

   strcpy(book, title);
   printf("Book name %s\n", book);
 }

