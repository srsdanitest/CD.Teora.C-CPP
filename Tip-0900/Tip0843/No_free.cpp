#include <iostream.h>

void main(void)
 {
   char *pointer;

   do 
   {
     pointer = new char[10000];

     if (pointer)
       cout << "Allocated 10,000 bytes\n";
     else
       cout << "Allocation failed\n";
   } while (pointer);
 }

