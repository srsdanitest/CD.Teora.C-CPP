//  If you use Visual C++, set the compile options to /GX
#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <vector.h>
#else
#include <iostream>
#include <vector>
#endif

using namespace std;
typedef vector<int> INTVECTOR;
const ARRAY_SIZE = 4;

void main(void)
{
   // Dynamically allocated vector begins with 0 elements.
   INTVECTOR theVector;

   // Intialize the array to contain the members [100, 200, 300, 400]
   for (int cEachItem = 0; cEachItem < ARRAY_SIZE; cEachItem++)
      theVector.push_back((cEachItem + 1) * 100);

   cout << "First element: " << theVector.front() << endl;
   cout << "Last element: " << theVector.back() << endl;
   cout << "Elements in vector: " << theVector.size() << endl;

   // Delete the last element of the vector. Remember that the vector
   // is 0-based, so theVector.end() actually points 1 element beyond
   // the end.
   cout << "Deleting last element." << endl;
   theVector.erase(theVector.end() - 1);
   cout << "New last element is: " << theVector.back() << endl;

   // Delete the first element of the vector.
   cout << "Deleting first element." << endl;
   theVector.erase(theVector.begin());
   cout << "New first element is: " << theVector.front() << endl;
   cout << "Elements in vector: " << theVector.size() << endl;
 }
