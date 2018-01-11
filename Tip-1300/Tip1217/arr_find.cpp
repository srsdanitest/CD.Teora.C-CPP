#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <algorith.h>
#else
#include <iostream>
#include <algorithm>
#endif

using namespace std ;

void main(void)
 {
   const int ARRAY_SIZE = 8;
   int IntArray[ARRAY_SIZE] = { 1, 2, 3, 4, 4, 5, 6, 7 };
   int *location ;	//stores the position of the first matching element.
   int i;
   int value = 4;

   // print content of IntArray
   cout << "IntArray { ";
   for (i = 0; i < ARRAY_SIZE; i++)
	   cout << IntArray[i] << ", ";
   cout << " }" << endl;

   //Find the first element in the range (first, last + 1)
   //that matches value.
   location = find(IntArray, IntArray + ARRAY_SIZE, value);
   
   //print the matching element if any was found
   if (location != IntArray + ARRAY_SIZE)	//matching element found
	   cout << "First element that matches " << value << " is at location "
	   << (location - IntArray) << endl;
   else										// no matching element found
	   cout << "The sequence does not contain any elements with value " << value << endl;
}



