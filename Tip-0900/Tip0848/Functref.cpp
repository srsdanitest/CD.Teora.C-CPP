#include <iostream.h>

void change_value(int& reference_value)
 {
   reference_value = 1500;
 }

void main(void)
 {
   int value = 10;
   int& alias = value;

   cout << "Value before function: " << value << '\n';

   change_value(alias);

   cout << "Value after function: " << value << '\n';
 }
