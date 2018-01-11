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
   double A[6] = { 1.2, 1.3, 1.4, 1.5, 1.6, 1.7 };
   int i;

   for (i = 0; i < 6; ++i)
     cout << "A[" << i << "] = " << A[i] << "  ";
   cout << endl;
   reverse(A, A + 6);
   for (i = 0; i < 6; ++i)
     cout << "A[" << i << "] = " << A[i] << "  ";
   cout << endl;
 }
