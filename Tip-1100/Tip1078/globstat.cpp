#include <iostream.h>

class SomeClass 
{
 public:
   static void message(void) { cout << "Hello, world!\n"; } ;
};

void main(void)
 {
   SomeClass::message();
 }
