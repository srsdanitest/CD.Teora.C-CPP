#include <iostream.h>
#include <iomanip.h>

class MagicNumbers 
{
 public:
   MagicNumbers(int a = 1, int b = 2, int c = 3)
     {
        MagicNumbers::a = a; 
        MagicNumbers::b = b;
        MagicNumbers::c = c;
     };
   void show_numbers(void)
     { 
       cout << a << ' ' << b << ' '<< c << '\n'; };
 private:
   int a, b, c;
};

void main(void)
 {
   MagicNumbers one(1, 1, 1);
   MagicNumbers defaults;
   MagicNumbers happy(101, 101, 101);

   one.show_numbers();
   defaults.show_numbers();
   happy.show_numbers();
 }






