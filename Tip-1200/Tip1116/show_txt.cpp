#include <iostream.h>

template <class T1, class T2> void sample(T1 x, T2 y);

void main(void)
 {
   sample(10, "hi");
   sample(0.23, 10L);
   sample("Jamsa's", "C/C++");
 }

template <class T1, class T2> void sample(T1 x, T2 y)
 {
   cout << x << " " << y << endl;
 }
