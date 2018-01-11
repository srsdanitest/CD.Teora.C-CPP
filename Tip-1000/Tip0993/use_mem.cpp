#include <iostream.h>

void main(void)
 {
   cout.setf(ios::hex);
   cout << 100 << endl;
   cout.unsetf(ios::hex);
   cout.fill('?');
   cout.width(10);
   cout << 2343.10 << endl;
 }
 