#include <iostream.h>

class base 
{
 public:
   int i;
 };

class derived1 : virtual public base 
{
 public:
   int j;
 };

class derived2 : virtual public base 
{
 public:
   int k;
 };

class derived3 : public derived1, public derived2 
{
 public:
   int sum;
 };

void main(void)
 {
   derived3 object;

   object.i = 10;             // now i is unambiguous
   object.j = 20;
   object.k = 30;
   object.sum = object.i + object.j + object.k;
   cout << object.i << " ";
   cout << object.j << " " << object.k << " ";
   cout << object.sum << endl;
 }


