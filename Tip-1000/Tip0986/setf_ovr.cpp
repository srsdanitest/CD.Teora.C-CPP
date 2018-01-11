#include <iostream.h>

void main(void)
 {
   cout.setf(ios::showpos | ios::showpoint);
   cout << 100 << endl;
   cout.setf(ios::showpoint, ios::showpos | ios::showpoint);
   cout << 100;
 }
