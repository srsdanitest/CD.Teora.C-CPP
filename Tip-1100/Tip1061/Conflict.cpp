#include <iostream.h>

class Base 
{
 public:
   void display(void) { cout << "This is the base class" << endl; };
};

class Derived: public Base 
{
 public:
   void display(void) { cout << "This is the derived class" << endl; };
};

void main(void)
 {
   Derived my_class;

   my_class.display();
 }

