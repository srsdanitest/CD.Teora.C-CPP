#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char * p;
   ostrstream outs;

   outs << "Jamsa's C/C++ ";
   outs << "Programmer's Bible ";
   outs << "has cool programs." << ends;
   p = outs.str();
   cout << p;
   delete p;
 }


