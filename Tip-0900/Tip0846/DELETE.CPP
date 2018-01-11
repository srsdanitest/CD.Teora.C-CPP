#include <iostream.h>

void main(void)
 {
   char *array = new char[256];
   char *target, *destination;
   
   int i;

   target = new char[256];
   for (i = 0; i < 256; i++)
    {
     array[i] = 'A';
     target[i] = 'B';
    }

   delete array;

   destination = new char[256];
   for (i = 0; i < 256; i++)
    {
     destination[i] = target[i];
     cout << destination[i] << ' ';
    }

   delete target;
   delete destination;
 }
