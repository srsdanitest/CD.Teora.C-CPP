#include <iostream.h>

class sample
  {
  int a, b;
  public:
    friend int sum(sample x);
    void set_ab(int i, int j);
  };

void sample::set_ab(int i, int j)
  {
  a = i;
  b = j;
  }

int sum(sample object)
  {
  /* Because sum is a friend of sample, it can access a and b directly */
  return object.a + object.b;
  }

void main(void)
  {
  sample integer;

  cout << "Adding 3 and 4:" <<j endl;
  integer.set_ab(3,4);
  cout << sum(integer);
  }

