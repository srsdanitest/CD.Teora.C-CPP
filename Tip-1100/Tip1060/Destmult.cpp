#include <iostream.h>

class One 
{
 public:
  One(void) { cout << "Constructor for One\n"; };
  ~One(void) { cout << "Destructor for One\n"; };
};

class Two 
{
 public:
  Two(void) { cout << "Constructor for Two\n"; };
  ~Two(void) { cout << "Destructor for Two\n"; };
};

class Three 
{
 public:
  Three(void) { cout << "Constructor for Three\n"; };
  ~Three(void) { cout << "Destructor for Three\n"; };
};


class Derived: public One, public Two, public Three 
{
 public:
   Derived(void) : One(), Two(), Three() 
   { cout << "Derived constructor called\n"; };
   ~Derived(void) 
   { cout << "Derived destructor called\n"; };
};

void main(void)
 {
   Derived my_class;
 }

