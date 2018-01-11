#include <iostream.h>

bool func(void)
 {    				// Function returns a bool type
   return false;
   //  return NULL;  // NULL is converted to Boolean false
 }

void main(void) 
{
   bool val = false;  // Boolean variable
   int i = 1;         // i is neither Boolean-true nor Boolean-false
   int g = 3;
   int *iptr = 0;     // null pointer
   float j = 1.01;    // j is neither Boolean-true nor Boolean-false

   if (i == true)
      cout << "True: value is 1" << endl;
   if (i == false)
      cout << "False: value is 0" << endl;
   if (g)
      cout << "g is true.";
   else
      cout << "g is false.";

   // Test on pointer
   if (*iptr == false)
      cout << "Invalid pointer." << endl;
   if (*iptr == true)
      cout << "Valid pointer." << endl;

   // To test j's truth value, cast it to bool type.
   if (bool(j) == true)
      cout << "Boolean j is true." << endl;

   // Test Boolean function return value

   val = func();
   if (val == false)
      cout << "func() returned false.";
   if (val == true)
      cout << "func() returned true.";
}
