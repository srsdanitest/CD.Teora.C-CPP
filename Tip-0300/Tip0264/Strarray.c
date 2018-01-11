#include <stdio.h>

int strlen(char str[])
 {
   int i = 0;

   while (str[i] != NULL)
     i++;

   return(i);
 }

void main(void)
 {
   printf("Length of ABC is %d\n", strlen("ABC"));
   printf("Length of Jamsa\'s C/C++ Programmer\'s Bible is %d\n",
     strlen("Jamsa\'s C/C++ Programmer\'s Bible"));
   printf("Length of a NULL string is %d\n", strlen(""));
 }

