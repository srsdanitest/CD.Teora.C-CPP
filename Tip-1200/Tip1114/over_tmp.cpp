#include <iostream.h>

template <class X> void swap(X &a, X &b);
void swap(int &a, int &b);

int main(void)
 {
   int i=10, j=20;
   float x=10.1, y=23.3;
   char a='x', b='z';

   cout << "Original i, j: " << i << " " << j << endl;
   cout << "Original x, y: " << x << " " << y << endl;
   cout << "Original a, b: " << a << " " << b << endl;
   swap(i,j);                                   // explicitly overloaded swap
   swap(a,b);
   swap(x,y);
   cout << "Swapped i, j: " << i << " " << j << endl;
   cout << "Swapped x, y: " << x << " " << y << endl;
   cout << "Swapped a, b: " << a << " " << b << endl;
 }

template <class X> void swap(X &a, X &b)
 {
   X temp;

   temp = a;
   a = b;
   b = temp;
 }

void swap(int &a, int &b)
 {
   int temp;

   temp = a;
   a = b;
   b = temp;
   cout << "Inside overloaded swap function." << endl;
 }


