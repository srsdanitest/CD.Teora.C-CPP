#include <iostream.h>

class pwr {
   double b;
   int e;
   double val;
 public:
   pwr(double base, int exp);
   pwr operator+(pwr obj) 
   {
      double base;
      int exp; 
      base = b + obj.b;
      exp = e + obj.e;
      pwr temp(base, exp);
      return temp;
   }
   operator double(void) {return val;}     // converts to double
 };

pwr::pwr(double base, int exp)
 {
   b = base;
   e = exp;
   val = 1;
   if (exp!=0)
      while(exp-- > 0)
         val *= b;
 }


void main(void)
 {
   pwr pwr1(4.0, 2);
   double doub1;

   doub1 = pwr1;                  // convert x to double
   cout << (doub1 + 100.2) << endl;

   pwr pwr2(3.3, 3), pwr3(0,0);
   pwr3 = pwr1 + pwr2;              // no conversion
   doub1 = pwr3;                  // convert to double
   cout << doub1;
 }



