#include <iostream.h>

class convert 
{
 protected:
   double val1;
   double val2;
 public:
   convert(double i)
    {
      val1 = i;
    }
    double getconv(void) {return val2;}
    double getinit(void) {return val1;}
    virtual void compute(void) = 0;
 };

// liters to gallons
class l_to_g : public convert {
 public:
   l_to_g(double i) : convert(i) { }
   void compute(void)
    {
      val2 = val1 / 3.7854;
    }
 };

// Fahrenheit to Celsius
class f_to_c : public convert {
 public:
   f_to_c(double i) : convert(i) { }
   void compute(void)
    {
      val2 = (val1 - 32) / 1.8;
    }
 };

void main(void)
 {
   convert *p;                    // pointer to base class

   l_to_g lgob(4);
   f_to_c fcob(70);

   p = &lgob;                    // convert liters to gallons
   cout << p->getinit() << " liters is ";
   p->compute();
   cout << p->getconv() << " gallons." << endl;

   p = &fcob;                    // convert fahrenheit to celsius
   cout << p->getinit() << " in Fahrenheit is ";
   p->compute();
   cout << p->getconv() << " Celsius." << endl;
 }
