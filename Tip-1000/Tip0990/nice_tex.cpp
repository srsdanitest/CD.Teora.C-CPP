#include <iostream.h>

void main(void)
 {
   cout.precision(4);
   cout.width(10);
   cout << 10.12345 << endl;
   cout.width(10);
   cout.fill('-');
   cout << 10.12345 << endl;
   cout.width(10);
   cout << "Hi!" << endl;
   cout.width(10);
   cout.setf(ios::left);
   cout << 10.12345;
 }