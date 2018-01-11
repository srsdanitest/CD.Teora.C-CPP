//  If you use Visual C++, set the compile options to /GX
#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <vector.h>
#include <algorith.h>
#else
#include <iostream>
#include <vector>
#include <algorithm>
#endif

using namespace std;

void PrintCube(int n)
{
    // prints the cube of integer n

    cout << "The cube of " << n << " is " << n * n * n << endl;
}

void main(void)
{
    const int VECTOR_SIZE = 8 ;
    typedef vector<int > IntVector ;		// Define a vector of integers
    typedef IntVector::iterator IntVectorIt ;	// Define an iterator type

    IntVector Numbers(VECTOR_SIZE) ;		//vector containing numbers
    IntVectorIt start, end, it ;			// iterators
    int i ;

    // Initialize vector Numbers
    for (i = 0; i < VECTOR_SIZE; i++)
        Numbers[i] = i + 1 ;

    start = Numbers.begin() ;   // location of first element of Numbers
    end = Numbers.end() ;       // one past the location last element of Numbers

    // print content of Numbers
    cout << "Numbers { " ;
    for(it = start; it != end; it++)
        cout << *it << " " ;
    cout << " }\n" <<endl ;

    // for each element in the range (first, last), print the element’s cube 
    for_each(start, end, PrintCube);
}
