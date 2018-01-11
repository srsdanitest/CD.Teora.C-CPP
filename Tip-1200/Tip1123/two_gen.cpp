#include <iostream.h>

template <class T1, class T2> class two_gen {
   T1 i;
   T2 j;
 public:
   two_gen(T1 a, T2 b)
      { i=a; j=b;}
   void show(void)
      { cout << i << " " << j << endl; }
 };

void main(void)
 {
   two_gen<int, double> obj1(10, 0.23);
   two_gen<char, char *> obj2('X', "This is a test.");

   obj1.show();
   obj2.show();
 }
