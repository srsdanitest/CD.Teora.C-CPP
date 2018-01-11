#include <iostream.h>

class loc 
{
  int longitude, latitude;
  public:
    loc(void) {}                //  Used to construct temporaries
    loc (int lg, int lt)
      {
      longitude = lg;
      latitude = lt;
      }

    void show(void)
      {
      cout << longitude << " ";
      cout << latitude << endl;
      }

    loc operator=(loc op2);
    friend loc operator+(loc op1, int op2);   //  Friend overloaded
    friend loc operator+(int op1, loc op2);   //  Friend overloaded
  };

loc loc::operator=(loc op2)
  {
  longitude = op2.longitude;
  latitude = op2.latitude;

  return *this;
  }

loc operator+(loc op1, int op2)
  {
  loc temp;

  temp.longitude = op1.longitude + op2;
  temp.latitude = op1.latitude + op2;

  return temp;
  }

loc operator+(int op1, loc op2)
  {
  loc temp;

  temp.longitude = op1 + op2.longitude;
  temp.latitude = op1 + op2.latitude;

  return temp;
  }


void main(void)
  {
  loc ob1(10,20), ob2( 5,30), ob3( 7,14);

  ob1.show();
  ob2.show();
  ob3.show();
  ob1 = ob2 + 10;
  ob3 = 10 + ob3;
  ob1.show();
  ob3.show();
  }
