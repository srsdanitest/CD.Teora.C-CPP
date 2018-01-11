#ifdef __BCPLUSPLUS__
#include <list.h>
#else
#include <list>
#endif
#include <iostream.h>
#include <string.h>

using namespace std;
typedef list<string> LISTSTR;

// Try each of the four constructors
void main(void)
 {
   LISTSTR::iterator i;
   LISTSTR test; 					// default constructor

   test.insert(test.end(), "one");
   test.insert(test.end(), "two");

   LISTSTR test2(test);            			// construct from another list
   LISTSTR test3(3, "three");      			// construct with three elements
    							// containing the value "three" 
   LISTSTR test4(++test3.begin(),test3.end());	// create from part of test3

   // Print them all out
   for (i =  test.begin(); i != test.end(); ++i)
     cout << *i << " ";
   cout << endl;

   for (i =  test2.begin(); i != test2.end(); ++i)
     cout << *i << " ";
   cout << endl;

   for (i =  test3.begin(); i != test3.end(); ++i)
     cout << *i << " ";
   cout << endl;

   for (i =  test4.begin(); i != test4.end(); ++i)
     cout << *i << " ";
   cout << endl;
 }
