#include <iostream.h>

void swap(int *a, int *b)
 {
   int temp = *a;
   *a = *b;
   *b = temp;
 }

void swap(int *a, int *b, int *c, int *d)
 {
   int temp = *a;
   *a = *b;
   *b = temp;
   temp = *c;
   *c = *d;
   *d = temp;
 }

void main(void)
 {
   int a = 1, b = 2 , c = 3, d = 4;

   swap(&a, &b);

   cout << "Just swapped a and b " << a << b << '\n';
   swap(&a, &b, &c, &d);
   cout << "Just swapped four " << a << b << c << d << '\n';
 }

