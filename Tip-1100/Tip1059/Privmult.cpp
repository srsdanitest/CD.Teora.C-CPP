#include <iostream.h>

class One 
{
 public:
  One(void) 
  { 
    cout << "Constructor for One\n"; 
    one = 1;
  };
  int one;
};

class Two 
{
 public:
  Two(void) 
  { 
    cout << "Constructor for Two\n";
    two = 2;
  };
  int two;
};

class Three 
{
 public:
  Three(void) 
  { 
    cout << "Constructor for Three\n"; 
    three = 3;
  };
  int three;
};


class Derived: private One, private Three, public Two 
{
 public:
   Derived(void) : One(), Two(), Three() 
   {
     cout << "Derived constructor called\n"; };

   void show_value(void) { cout << one << two << three << endl; };
};

void main(void)
 {
   Derived my_class;
   my_class.show_value();
   cout << my_class.two;
 }

