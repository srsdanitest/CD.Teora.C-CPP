#include <iostream.h>

class Base 
{
 public:
   void base_message(void) { cout << "This is the base class\n"; };
};

class Derived: public Base 
{
 public:
   void derived_message(void) { cout << "This is the derived class\n" ; };
};

void main(void)
 {
   Base *base_pointer = new Base;
   base_pointer->base_message();
   
   base_pointer = new Derived;
   base_pointer->base_message();
 }

