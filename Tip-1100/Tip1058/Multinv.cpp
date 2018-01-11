#include <iostream.h>

class One 
{
 public:
  One(void) { cout << "Constructor for One\n"; };
};

class Two 
{
 public:
  Two(void) { cout << "Constructor for Two\n"; };
};

class Three 
{
 public:
  Three(void) { cout << "Constructor for Three\n"; };
};

class Derived: public One, public Three, public Two 
{
 public:
   Derived(void) : One(), Two(), Three() 
   {
     cout << "Derived constructor called\n"; };
};

void main(void)
 {
   Derived my_class;
 }

