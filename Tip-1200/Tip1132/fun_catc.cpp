#include <iostream.h>

void XHandler(int test)
 {
   try {
      if(test) throw test;
    }
   catch(int i)
    {
      cout << "Caught exception #: " << i << endl;
    }
 }

void main(void)
 {
   cout << "Start: " << endl;
   XHandler(1);
   XHandler(2);
   XHandler(0);
   XHandler(3);
   cout << "End";
 }

