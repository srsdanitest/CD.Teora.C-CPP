#include <iostream.h>
#include <stdlib.h>

class sometype {
	int a[3];
  public:
   sometype(int i, int j, int k)
    {
      a[0] = i;
      a[1] = j;
      a[2] = k;
    }
   int &operator[](int i);
  };

int &sometype::operator[](int i)
 {
   if (i<0 || i>2)
    {
      cout << "Boundary error.\n";
      exit(1);
    }
   return a[i];
 }


void main(void)
{
   sometype ob(1, 2, 3);

   cout << ob[1];
   cout << endl;
   ob[1] = 25;
   cout << endl;
   cout << ob[1];
   ob[3] = 44;
}

