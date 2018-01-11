#include <iostream.h>

void XHandler(int test)
 {
    cout << "Inside XHandler, test is:" << test << endl;
    if(test) throw test;
 }

void main(void)
 {
   cout << "Start: " << endl;
   try {
      cout << "Inside try block." << endl;
      XHandler(1);
      XHandler(2);
      XHandler(0);
    }
   catch(int i) {
      cout << "Caught an exception. Value is: ";
      cout << i << endl;
    }
   cout << "End";
 }

