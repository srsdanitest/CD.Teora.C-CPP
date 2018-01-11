#include <iostream.h>

void XHandler(int test)
 {
   try 
   {
      if(test==0) throw test;
      if(test==1) throw 'a';
      if(test==2) throw 123.23;
    }
   catch(...)
    {
      cout << "Caught one." << endl;
    }
 }

void main(void)
 {
   cout << "Start: " << endl;
   XHandler(0);
   XHandler(1);
   XHandler(2);
   cout << "End";
 }
 
