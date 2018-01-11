#include <iostream.h>

class Base 
{
 public:
   Base(void) { cout << "Base class constructor\n"; };
};

class Derived:Base 
{
 public:
   Derived(void): Base() 
    { cout << "Derived class constructor\n"; };
};

void main(void)
 {
   Derived object;
 }

