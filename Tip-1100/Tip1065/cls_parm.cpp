#include <iostream.h>

class base 
{
 protected:
   int i;
 public:
   base(int x) 
   {
     i=x;
     cout << "Constructing base.\n";
   }
   ~base(void) {cout << "Destructing base.\n";}
 };

class derived : public base 
{
   int j;
 public:
   // derived uses x; base uses y.
   derived(int x, int y): base(y)
     {
	   j=x; 
	   cout << "Constructing derived.\n";
   }
   ~derived(void) {cout << "Destructing derived.\n";}
   void show(void) {cout << i << ", " << j << endl;}
 };

void main(void)
 {
   derived object(3,4);

   object.show();                // Displays 4, 3
 }


