#include <stdio.h>
#include <conio.h>

void main(void)
 {
   printf("Press any key to continue...");

   while (! kbhit());
     ;
   printf("Done\n");
 }
