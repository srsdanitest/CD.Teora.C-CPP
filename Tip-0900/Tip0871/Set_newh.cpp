#include <iostream.h>
#include <stdlib.h>
#include <new.h>

void no_memory(void)
 {
   cerr << "There is no more memory to allocate...\n";
   exit(0);
 }

void main(void)
 {
   char *ptr;

   set_new_handler(no_memory);

   do 
   {
     ptr = new char[10000];

     if (ptr)
       cout << "Just allocated 10,000 bytes\n";
   } while (ptr);
 }
