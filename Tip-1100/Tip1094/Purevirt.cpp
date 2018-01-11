#include <iostream.h>
#include <string.h>

class Base 
{
 public:
   virtual void show_message(void) { cout << "Base class message" << endl; };
   virtual void show_reverse(void) = 0;
};

class Derived : public Base 
{
 public:
   virtual void show_message(void) { cout << "Derived class message" << endl; };
   virtual void show_reverse(void) { cout << strrev("Derived class message") << endl; };
};

void main(void)
 {
   Base *poly = new Derived;
   poly->show_message();
   poly->show_reverse();
 }


