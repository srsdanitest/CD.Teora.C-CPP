#include <iostream.h>

class sample {
 public:
   int i;
   sample *operator->(void) {return this;}
 };

void main(void)
 {
   sample obj;

   obj->i = 10;						// Same as obj.i
   cout << obj.i << " " << obj->i;
 }
