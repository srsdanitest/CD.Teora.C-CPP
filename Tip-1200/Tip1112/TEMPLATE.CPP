#include <iostream.h>

template<class T, class T1> T add_values(T a, T1 b)
  {
    return(a + b);
  }

long add_values(long a, int b);
double add_values(double a, float b);

void main(void)
 {
   long a = 320000L;
   int b = 31000; 

   double c = 22.0 / 7.0;
   float d = 3.145;

   cout << "Adding " << a << ' ' << b << ' ' << add_values(a, b) << 
endl;
   cout << "Adding " << c << ' ' << d << ' ' << add_values(c, d) << 
endl;
 }
