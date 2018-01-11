#include <iostream.h>

class base 
{
   int i;         // private in base class
 public:
   int j, k;
   void seti(int x) {i = x;}
   int geti(void) {return i;}
 };

class derived : private base 
{
 public:
                  // The next statements override the private inheritance.
   base::j;       // makes j public again
   base::seti;    // makes seti() public
   base::geti;    // makes geti() public
   // base::i; is an illegal statement, you cannot promote access.
   int a;
 };

void main(void)
 {
   derived object;

   //object.i = 10;  Illegal statement; i is private to base.
   object.j = 20; // legal because j is public

   //object.k = 30; Illegal because k is private to derived
   object.a = 40;
   object.seti(10);
   cout << object.geti() << ", " << object.j << ", " << object.a;
 }

 


