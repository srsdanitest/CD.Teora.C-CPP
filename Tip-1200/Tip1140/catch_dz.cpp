#include <iostream.h>

void divide(double a, double b)
 {
   try {
      if(!b) throw b;            // checks for divide-by-zero
      cout << "Result: " << a/b << endl;
    }
   catch(double b) {
      cout << "Can't divide by zero." << endl;
    }
 }


void main(void)
 {
   double i, j;

   do {
      cout << "Enter numerator (0 to stop):" << endl;
      cin >> i;
      cout << "Enter denominator: " << endl;
      cin >> j;
      divide (i,j);
    }
   while (i !=0);
   
 }


