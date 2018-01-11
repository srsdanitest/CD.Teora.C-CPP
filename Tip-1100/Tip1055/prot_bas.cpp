#include <iostream.h>

class base 
{
 protected:
   int i, j;
 public:
   void setij(int a, int b) 
   {
     i=a; 
     j=b;
   }
   void showij(void) {cout << i << " " << j << endl;}
 };

class derived : protected base 
{
 private:
   int k;
 public:
   void setk(void) 
   {
     setij(10,12); 
     k = i * j;
   }
   void showall(void) 
   {
     cout << k << " "; 
     showij();
   }
 };

void main(void)
 {
   derived object;

   // object.setij(2,3);   This is an illegal command, because setij is a protected member of derived.
   // object.showij();      This is also an illegal command.

   object.setk();
   object.showall();
 }


