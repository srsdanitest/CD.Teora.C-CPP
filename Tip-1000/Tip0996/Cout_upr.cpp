#include <iostream.h>
#include <string.h>

ostream& operator<<(ostream& cout, char *string)
 {
   char *str = strupr(string);
   
   while (*str)
     cout.put(*str++);

   return(cout);
 }

void main(void)
 {
   cout << "This is a test";
   cout << "\nJamsa's C/C++ Programmer's Bible";
 }

