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

    friend loc operator+(loc op1, loc op2);   //  Friend overloader
    loc operator=(loc op2);
  };

loc operator+(loc op1, loc op2)
  {
  loc temp;
  
  temp.longitude = op1.longitude + op2.longitude;
  temp.latitude = op1.latitude + op2.latitude;
  return temp;
  }

loc loc::operator=(loc op2)
  {
  longitude = op2.longitude;
  latitude = op2.latitude;

  return *this;
  }

void main(void)
  {
  loc ob1(10,20), ob2(5,30);

  ob1 = ob1+ob2;
  ob1.show();
  }