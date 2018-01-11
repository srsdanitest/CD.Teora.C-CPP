#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char string[256];
   
   ostrstream str(string, 256);									// Bind the string
   str << "Jamsa's C/C++ Programmer's Bible" << ends;
   cout << string;
 }

