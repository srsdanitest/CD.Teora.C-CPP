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
    void show();
  };

int shared::a;		//	Define the a global variable

void shared::show()
  {
  cout << "This is static a: " << a << endl;
  cout << "This is non-static b: " << b << endl;
  }

void main(void)
  {
  shared x, y;

  x.set(1,1);
  x.show();
  y.set(2,2);
  y.show();
  x.show();
  }







