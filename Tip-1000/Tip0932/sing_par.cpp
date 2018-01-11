#include <iostream.h>

class simple
  {
  int a;
  public:
    simple(int j) {a = j;}
    int geta(void) {return a;}
  };

void main(void)
  {
  simple ob = 99;              // passes 99 to j

  cout << ob.geta();
  }


