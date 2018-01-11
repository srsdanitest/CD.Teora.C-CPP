#include <iostream.h>

void main(void)
 {
   cout << "Start" << endl;
   try {
      cout << "Inside try block." << endl;
      throw 100;
      cout << "This will not execute.";
    }
   catch(double d) {
      cout << "Caught a double exception -- value is: ";
      cout << d << endl;
    }
   cout << "End";
 }
 