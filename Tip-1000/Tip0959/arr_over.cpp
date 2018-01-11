#include <iostream.h>

class sometype 
{
	int a[3];
  public:
   sometype(int i, int j, int k)
    {
      a[0] = i;
      a[1] = j;
      a[2] = k;
    }
   int operator[](int i) {return a[i];}
  };

void main(void)
{
   sometype ob(1, 2, 3);

   cout << ob[1];
}

