// This program contains three errors and will not compile.
#include <iostream.h>

class base 
{
 public:
   int i;
 };

class derived1 : public base 
{
 public:
   int j;
 };

class derived2 : public base 
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

   object.i = 10;         // This causes the compiler to halt because 
            						  //it doesn't know which i you are referring to.
   object.j = 20;
   object.k = 30;
   object.sum = object.i + object.j + object.k;
   cout << object.i << " ";
   cout << object.j << " " << object.k << " ";
   cout << object.sum << endl;
 }
 

