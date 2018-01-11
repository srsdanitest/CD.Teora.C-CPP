#include <iostream.h>
#include "stdlib.h"

const int SIZE = 10;

template <class AType> class atype {
   AType a[SIZE];
 public:
   atype(void)
    {
      int i;

      for(i=0; i<SIZE; i++)
         a[i] = i;
    }
   AType &operator[](int i);
 };

template <class AType> AType &atype<AType>::operator[](int i)
 {
   if(i<0 || i> SIZE-1)
    {
      cout << endl << "Index value of ";
      cout << i << " is out of bounds." << endl;
    }
   return a[i];
 }

void main(void)
 {
   atype<int> int_array;
   atype<double> double_array;
   int i;

   cout << "Integer array: ";
   for(i=0; i<SIZE; i++)
      int_array[i] = i;
   for(i=0; i<SIZE; i++)
      cout << int_array[i] << " ";
   cout << endl;

   cout << "Double array: ";
   cout.precision(2);
   for(i=0; i<SIZE; i++)
      double_array[i] = (double)i/3;
   for(i=0; i<SIZE; i++)
      cout << double_array[i] << " ";
   cout << endl;

   int_array[12] = 100;                 // Calls overloaded array operator
 }

