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


void main(void)
{
    const int VECTOR_SIZE = 8 ;

    // Define a template class vector of int
    typedef vector<int> IntVector ;

    //Define an iterator for template class vector of strings
    typedef IntVector::iterator IntVectorIt ;

    IntVector Numbers(VECTOR_SIZE) ;

    IntVectorIt start, end, it ;

    // Initialize vector Numbers
    Numbers[0] = 4 ;
    Numbers[1] = 10;
    Numbers[2] = 70 ;
    Numbers[3] = 30 ;
    Numbers[4] = 10;
    Numbers[5] = 69 ;
    Numbers[6] = 96 ;
    Numbers[7] = 100;

    start = Numbers.begin() ;   // location of first
                                // element of Numbers

    end = Numbers.end() ;       // one past the location
                                // last element of Numbers

    cout << "Before calling random_shuffle\n" <<endl ;

    // print content of Numbers
    cout << "Numbers { " ;
    for(it = start; it != end; it++)
        cout << *it << " " ;
    cout << "\b }\n" <<endl ;

    // shuffle the elements in a random order
    random_shuffle(start, end) ;

    cout << "After calling random_shuffle\n" <<endl ;

    cout << "Numbers { " ;
    for(it = start; it != end; it++)
        cout << *it << " " ;
    cout << "\b }\n" <<endl ;
}
