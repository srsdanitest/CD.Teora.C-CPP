#include <iostream.h>
#include <iomanip.h>

void call_by_value(int a, int b, int c)
 {
   a = 3; b = 2; c = 1;
 }

void call_by_pointer_reference(int *a, int *b, int *c)
 {
   *a = 3; *b = 2; *c = 1;
 }

void call_by_reference(int& a, int& b, int& c)
 {
   a = 1; b = 2; c = 3;
 }

void main(void)
 {
   int a = 1, b = 2, c = 3;
   int& a_alias = a; 
   int& b_alias = b;
   int& c_alias = c;  

   call_by_value(a, b, c);
   cout << "By value: " << a << b << c << '\n';

   call_by_pointer_reference(&a, &b, &c);
   cout << "By pointer: " << a << b << c << '\n';

   call_by_reference(a_alias, b_alias, c_alias);
   cout << "By reference: " << a << b << c << '\n';
 }
