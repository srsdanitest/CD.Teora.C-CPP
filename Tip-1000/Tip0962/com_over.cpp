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
    loc operator,(loc op2);
  };

loc loc::operator,(loc op2)
 {
   loc temp;

   temp.longitude = op2.longitude;
   temp.latitude = op2.latitude;
   cout << op2.longitude << "  " << op2.latitude << endl;
   return temp;
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
   loc obj1(10,20), obj2( 5,30), obj3(1,1), temp;

   obj1.show();
   obj2.show();
   obj3.show();
   cout << endl;
   obj1 = (obj1, obj2 + obj2, obj2 + obj3);
   obj1.show();                      // Will display 6,31, obj2 + obj3's value
  }
