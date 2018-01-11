//  If you use Visual C++, set the compile options to /GX

#ifdef __BCPLUSPLUS__
#include <iostream.h>
#include <list.h>
#else
#include <iostream>
#include <list>
#endif

using namespace std;
typedef list<int> LISTINT;

void main(void)
 {
   LISTINT listOne;
   LISTINT::iterator i;

   // Add some data
   listOne.push_front (2);
   listOne.push_front (1);
   listOne.push_back (3);

   // 1 2 3
   for (i = listOne.begin(); i != listOne.end(); ++i)
     cout << *i << " ";
   cout << endl;

   // 1 1 1 1
   for (i = listOne.end(); i != listOne.begin(); --i)
     cout << *i << " ";
   cout << endl;

 }
