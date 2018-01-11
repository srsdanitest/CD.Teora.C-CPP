#include <iostream.h>

void main(void)
 {
   char far *pointer;

   do 
   {
     pointer = new far char[10000];

     if (pointer)
       cout << "Allocated 10,000 bytes\n";
     else
       cout << "Allocation failed\n";
   } while (pointer);
 }

