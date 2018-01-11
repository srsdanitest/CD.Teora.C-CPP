#include <iostream.h>

void main(void)
 {
   int i;
   char *p = "This is a string.";

   i = reinterpret_cast<int> (p);         // cast char pointer to integer
   cout << i;
   
 }
