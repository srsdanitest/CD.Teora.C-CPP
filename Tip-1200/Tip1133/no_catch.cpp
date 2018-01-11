#include <iostream.h>

void main(void)
 {
   cout << "Start" << endl;
   try 
   {
      cout << "Inside try block." << endl;
      cout << "Still inside try block." << endl;
    }
   catch(int i) 
   {
      cout << "Caught an exception--value is: " << endl;
      cout << i << endl;
    }
   cout << "End";
 
 }




