#include <iostream.h>

void XHandler(int test)
 {
   try 
   {
      if(test==0) throw test;
      if(test==1) throw "String";
      if(test==2) throw 123.23;
    }
   catch(int i)
    {
      cout << "Caught exception #: " << i << endl;
    }
   catch(char *str)
    {
      cout << "Caught string exception: " << str << endl;
    }
   catch(double d)
    {
      cout << "Caught exception #: " << d << endl;
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
 
