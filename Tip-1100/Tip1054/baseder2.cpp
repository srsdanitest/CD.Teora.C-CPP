#include <iostream.h>

class Base 
{
 public:
   Base(void) { cout << "Base class constructor\n"; };
   int data; 
};

class Derived:public Base 
{
 public:
   Derived(void): Base() 
    { cout << "Derived class constructor\n"; };
};

void main(void)
 {
   Derived object;
   object.data = 5;
   cout << object.data << endl;
 }
