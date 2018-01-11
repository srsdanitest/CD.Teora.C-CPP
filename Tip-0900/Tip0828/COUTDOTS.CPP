#include <iostream.h>

void main(void)
 {
   int i;

   for (i = 0; i < 3; i++)
    {
     cout.fill('.');
     cout.width(5 + i);
     cout << i << '\n';
    }
 }
