#include <iostream.h>
#include <typeinfo.h>

class A { };
class B : A { };

void main(void)
 {
   char C;
   float X;

   //USE THE typeinfo::operator == () TO MAKE COMPARISON
   if (typeid( C ) == typeid( X ))                    
      cout << "C and X are the same type." << endl;
   else
      cout << "C and X are NOT the same type." << endl;

   // USE true AND false LITERALS TO MAKE COMPARISON
   cout << typeid(int).name();                       
   cout << " before " << typeid(double).name() << ": " <<
        (typeid(int).before(typeid(double)) ? true : false) << endl;
   cout << typeid(double).name();
   cout << " before " << typeid(int).name() << ": " <<
        (typeid(double).before(typeid(int)) ? true : false) << endl;
   cout << typeid(A).name();
   cout << " before " << typeid(B).name() << ": " <<
        (typeid(A).before(typeid(B)) ? true : false) << endl;
 }
