#include <iostream.h>

void main(void)
 {
   cout.setf(ios::uppercase | ios::scientific);
   cout << 100.12;
   cout.unsetf(ios::uppercase);
   cout << endl << 100.12;
 }

