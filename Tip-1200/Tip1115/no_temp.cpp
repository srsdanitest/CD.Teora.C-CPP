#include <iostream.h>
#include <math.h>

void non_template(int i)
 {
   cout << "value is: " << i << endl;
 }

void non_template(double d)
 {
   double intpart;
   double fracpart;

   fracpart = modf(d, &intpart);
   cout << "Fractional part: " << fracpart << endl;
   cout << "Integer part: " << intpart << endl;
 }

void main(void)
 {
   non_template(1);
   non_template(12.2);
 }
 


