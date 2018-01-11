#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char str[80];
   ostrstream outs(str, sizeof(str));

   outs << "Hello ";
   outs << 34 << "  " << 9876.98;
   outs << ends;
   cout << "String length: " << outs.pcount() << endl;
   cout << str;
 }

