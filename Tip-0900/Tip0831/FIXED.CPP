#include <iostream.h>
#include <iomanip.h>

void main(void)
 {
   float value = 0.000123;

   cout << setiosflags(ios::fixed) << value << '\n';
   cout << setiosflags(ios::scientific) << value << '\n';
 }
