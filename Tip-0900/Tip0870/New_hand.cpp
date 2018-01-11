#include <iostream.h>
#include <stdlib.h>

extern void (*_new_handler)();

void no_memory(void)
 {
   cerr << "There is no more memory to allocate...\n";
   exit(0);
 }

void main(void)
 {
   _new_handler = no_memory;

   char *ptr;

   do 
   {
     ptr = new char[10000];

     if (ptr)
       cout << "Just allocated 10,000 bytes\n";
   } while (ptr);
 }
