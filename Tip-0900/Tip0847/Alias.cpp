#include <iostream.h>

void main(void)
 {
   int a = 1001;
   int& a_alias = a;
   float price = 39.95;
   float& price_alias = price;

   cout << "The value of a is " << a << " the alias is " << a_alias;
   cout << "\nThe price is " << price << " the alias is " << price_alias; 
  
   a_alias++;
   cout << "\nThe value of a is " << a << " the alias is " << a_alias;
 }
