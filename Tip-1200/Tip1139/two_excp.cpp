#include <iostream.h>

void XHandler(void)
 {
   try {
      throw "hello";
    }
   catch(char *) {
      cout << "Caught char * inside XHandler." << endl;
      throw;
    }
 }


void main(void)
 {
   cout << "Start: " << endl;
   try {
      XHandler();
    }
   catch(char *) 
   {
      cout << "Caught char * inside main." << endl;
    }
   cout << "End";
   
 }

