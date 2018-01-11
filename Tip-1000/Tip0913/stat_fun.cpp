#include <iostream.h>

class shared
  {
  	static int a;
    int b;
  public:
    void set(int i, int j) 
    {
      a=i;
      b=j;
    }
    static void show();
  };

int shared::a;		//	Define the a global variable

void shared::show()
  {
  cout << "This is static a: " << a << endl;
  }

void main(void)
  {
  shared x, y;

  x.set(1,1);
  y.set(2,2);
  shared::show();
  y.show();
  x.show();
  }







