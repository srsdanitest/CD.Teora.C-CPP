#ifdef __BCPLUSPLUS__
#include <list.h>
#else
#include <list>
#endif

#include <string.h>
#include <iostream.h>

using namespace std;
typedef list<string> LISTSTR;

void main(void)
 {
   LISTSTR test;

   test.push_back("back");
   test.push_front("middle");
   test.push_front("front");
   cout << test.front() << endl;		// front
   cout << test.back() << endl;		// back
   test.pop_front();
   test.pop_back();
   cout << test.front() << endl;		// middle
 }
