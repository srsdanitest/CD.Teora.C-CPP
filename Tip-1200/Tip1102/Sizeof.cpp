#include <iostream.h>
#include <string.h>

class Base {
 public:
   Base(char *message) { strcpy(Base::message, message); }; 
   void show_base(void) { cout << message << endl; };
 private:
   char message[256];
};

class Derived: public Base {
 public:
   Derived(char *dmsg, char *bmsg) : Base(bmsg) {
     strcpy(message, dmsg); };
   void show_derived(void) 
   { 
	 cout << message << endl; 
     show_base(); 
   };
 private:
   char message[256];
};

void main(void)
 {
   Base some_base("This is a base");
   Derived some_derived("Derived message", "Base message");

   cout << "The size of the base class is " << sizeof(some_base) << " bytes" << endl;
   cout << "The size of the derived class is " << sizeof(some_derived) << " bytes" << endl;
 }

