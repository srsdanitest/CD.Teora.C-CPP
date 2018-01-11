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
    friend loc operator++(loc &op1);   //  Friend overloaded
    friend loc operator--(loc &op1);   //  Friend overloaded
  };

loc loc::operator=(loc op2)
  {
  longitude = op2.longitude;
  latitude = op2.latitude;

  return *this;
  }

loc operator++(loc &op)
  {
  op.longitude++;
  op.latitude++;

  return op;
  }

loc operator--(loc &op)
  {
  op.longitude--;
  op.latitude--;

  return op;
  }

void main(void)
  {
  loc ob1(10,20), ob2;

  ob1.show();
  ++ob1;
  ob1.show();			// Displays 11 and 21
  ob2 = ++ob1;
  ob2.show();			//	Displays 12 and 22
  --ob2;
  ob2.show();			//	Displays 11 and 21 again
  }
