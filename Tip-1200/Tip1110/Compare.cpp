#include <iostream.h>

template<class T> T compare_values(T a, T b)
 {
   return((a > b) ? a: b);
 }

float compare_values(float a, float b);
int compare_values(int a, int b);
long compare_values(long a, long b);

void main(void)
 {
   float a = 1.2345, b = 2.34567;
   cout << "Comparing " << a << ' ' << b  << ' ' << 
compare_values(a, b) << endl;

   int c = 1, d = 1001;
   cout << "Comparing " << c << ' ' << d  << ' ' << 
compare_values(c, d) << endl;

   long e = 1010101L, f = 2020202L;
   cout << "Comparing " << e << ' ' << f  << ' ' << 
compare_values(e, f) << endl;
 }
