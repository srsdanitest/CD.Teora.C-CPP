#include <iostream.h>
#include <typeinfo.h>

class Base {
   int a, b;
   virtual void func(void) {};
 };

class Derived1: public Base {
   int i, j;
 }

class Derived2: public Base {
   int k;
 }

void main(void)
 {
   int i;
   Base *p, baseobj;
   Derived1 obj1;
   Derived2 obj2;

   cout << "Typeid of i is: ";
   cout << typeid(i).name() << endl;
   p = &baseobj;
   cout << "p is currently pointing to an object of type: ";
   cout << typeid(*p).name() << endl;
   p = & obj1;
   cout << "p is now pointing to an object of type: ";
   cout << typeid(*p).name() << endl;
   p = & obj2;
   cout << "p is finally pointing to an object of type: ";
   cout << typeid(*p).name() << endl;
 }
 