#include <iostream.h>
#include <iomanip.h>

void main(void)
 { 
   cout.width(5);
   cout << setiosflags(ios::left) << 5 << '\n'; 
   cout.width(5);
   cout << 5 << '\n' << resetiosflags(ios::left); 
   cout.width(5);
   cout << 1;
 }

