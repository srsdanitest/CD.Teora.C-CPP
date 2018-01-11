#include <iostream.h>

void XHandler(int test) throw(int, char, double)
 {
   if(test==0) throw test;
   if(test==1) throw 'a';
   if(test==2) throw 123.23;
 }

void main(void)
 {
   cout << "Start: " << endl;
   try {
      XHandler(0);                  // try passing 1 and 2 for different responses
    }
   catch(int i) {
      cout << "Caught an integer." << endl;
    }
   catch(char c) {
      cout << "Caught a character." << endl;
    }
   catch(double d) {
      cout << "Caught a double." << endl;
    }
   cout << "End";
  
 }
 
