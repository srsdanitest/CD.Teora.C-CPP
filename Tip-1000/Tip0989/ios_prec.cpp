#include <iostream.h>

void main(void)
 {
   int i;
   float value = 1.2345;

   for (i = 0; i < 4; i++)
    {
      cout.precision(i);
      cout << value << endl;
    }
 }

