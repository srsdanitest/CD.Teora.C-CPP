#include <iostream.h>

void main(void)
 {
   union 
   {
     int my_data;
     float his_data;
   };

   my_data = 3;

   cout << "Value of my_data is " << my_data;

   his_data = 1.2345;

   cout << "\nValue of his_data is " << his_data;
 }
