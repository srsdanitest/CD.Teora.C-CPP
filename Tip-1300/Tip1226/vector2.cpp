#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <vector.h>
#else
#include <iostream>
#include <vector>
#endif

using namespace std;
typedef vector<int> INTVECTOR;

void main(void)
 {
   // Dynamically allocated vector begins with 0 elements.
   INTVECTOR theVector;

   // Add one element to the end of the vector, an int with the value 42.
   theVector.push_back(42);

   // Show statistics about vector.
   cout << "theVector's size is: " << theVector.size() << endl;
   cout << "theVector's maximum size is: " << theVector.max_size()<< endl;
   cout << "theVector's capacity is: " << theVector.capacity() << endl;

   // Ensure there's room for at least 1000 elements.
   theVector.reserve(1000);
   cout << endl << "After reserving storage for 1000 elements:" << endl;
   cout << "theVector's size is: " << theVector.size() << endl;
   cout << "theVector's maximum size is: " << theVector.max_size()<< endl;
   cout << "theVector's capacity is: " << theVector.capacity() << endl;

   // Ensure there's room for at least 2000 elements.
   theVector.resize(2000);
   cout << endl << "After resizing storage to 2000 elements:" << endl;
   cout << "theVector's size is: " << theVector.size() << endl;
   cout << "theVector's maximum size is: " << theVector.max_size()<< endl;
   cout << "theVector's capacity is: " << theVector.capacity() << endl;
 }
