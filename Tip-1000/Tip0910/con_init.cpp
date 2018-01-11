#include <iostream.h>

class object
 {
   public: 
     object::object(void);
     void show_object(void);
   private:
     int a;
     int b;
     int c;
 };

object::object(void) : a(1), b(2), c(3) { };

void object::show_object(void)
 {
   cout << "a contains: " << a << endl;
   cout << "b contains: " << b << endl;
   cout << "c contains: " << c << endl;
 }

void main(void)
 {
   object numbers;

   numbers.show_object();
 }
