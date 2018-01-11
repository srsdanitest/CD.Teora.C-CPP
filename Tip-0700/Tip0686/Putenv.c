#include <stdio.h>
#include <stdlib.h>

void main(void)
 {
   if (putenv("BOOK=Jamsa\'s C & C++ Programmer\'s Bible"))
     printf("Error writing to environment\n");
   else
     {
       int i;

       for (i = 0; environ[i]; ++i)
         printf("%s\n", environ[i]);
     }
 }
