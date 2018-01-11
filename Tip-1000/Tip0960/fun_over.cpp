#include <iostream.h>

class loc {
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

    loc operator+(loc op2);
    loc operator()(int i, int j);
  };

loc loc::operator()(int i, int j)
 {
  longitude = i;
  latitude = j;
  return *this;
 }

loc loc::operator+(loc op2)
 {
   loc temp;


   temp.longitude = op2.longitude + longitude;
   temp.latitude = op2.latitude + latitude;
   return temp;
 }

void main(void)
  {
   loc ob1(10,20), ob2( 1,1);

   ob1.show();
   ob1(7,8);
   ob1.show();
   ob1 = ob2 + ob1(10,10);
   ob1.show();
  }
