#include <iostream.h>

void main(void)
 {
   char *array = new char[256];
   int i;

   for (i = 0; i < 256; i++)
     array[i] = 'A';

   for (i = 0; i < 256; i++)
     cout << array[i] << ' ';
 }
