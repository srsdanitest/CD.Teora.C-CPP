#include <iostream.h>
#include <stdlib.h>

class Base 
{
 public:
   virtual int add(int a, int b) { return(a + b); };
   virtual int sub(int a, int b) { return(a - b); };
   virtual int mult(int a, int b) { return(a * b); };
};

class ShowMath : public Base 
{
   virtual int mult(int a, int b) 
    { 
      cout << a * b << endl; 
      return(a * b); };
};

class PositiveSubt : public Base 
{
   virtual int sub(int a, int b) { return(abs(a - b)); };
};

void main(void)
 {
   Base *poly = new ShowMath;

   cout << poly->add(562, 531) << ' ' << poly->sub(1500, 407) << endl; 
   poly->mult(1093, 1);

   poly = new PositiveSubt;
   cout << poly->add(892, 201) << ' ' << poly->sub(0, 1093) << endl;
   cout << poly->mult(1, 1093);
 }

