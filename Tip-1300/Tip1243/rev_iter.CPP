#ifdef __BCPLUSPLUS__
#include <deque.h>
#else
#include <deque>
#endif

#include <iostream.h>

using namespace std;
typedef deque<int> INTDEQUE;

void main(void)
 {
   // Create A and fill it with elements 1,2,3,4 and 5 using push_back function

   INTDEQUE A;
   A.push_back(1);
   A.push_back(2);
   A.push_back(3);
   A.push_back(4);
   A.push_back(5);

   // Now print the contents in reverse order using reverse_iterator
   // and functions rbegin() and rend()

   INTDEQUE::reverse_iterator rpi;
   for(rpi = A.rbegin(); rpi != A.rend(); rpi++)
      cout << *rpi << " ";
   cout<< endl;
 }
