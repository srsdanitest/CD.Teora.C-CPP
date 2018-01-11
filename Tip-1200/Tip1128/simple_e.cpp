#include <iostream.h>

void main(void)
 {
   cout << "Start" << endl;
   try {
      cout << "Inside try block." << endl;
      throw 100;
      cout << "This will not execute.";
    }
   catch(int i) {
      cout << "Caught an exception -- value is: ";
      cout << i << endl;
    }
   cout << "End";
 }
 