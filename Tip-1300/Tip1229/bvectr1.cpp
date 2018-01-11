#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <bvector.h>
#else
#include <iostream>
#include <bvector>
#endif

using namespace std;
const ARRAY_SIZE = 4;

void main(void)
{
   // Dynamically allocated vector begins with 0 elements.
   bit_vector theVector(ARRAY_SIZE);

   // Intialize the array to contain the members [100, 200, 300, 400]
   for (int cEachItem = 0; cEachItem < ARRAY_SIZE; cEachItem++)
      if(cEachItem>1)
	      theVector.push_back(cEachItem - 2);
      else
         theVector.push_back(cEachItem);

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
