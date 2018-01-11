#include <iostream.h>

class sample 
{
   int value;
 public:
   sample(int j) {value = j;}        // constructor
   int get_value(void) {return value;}
 };

void main(void)
 {
  int loop;
   sample obj[3] = {1 , 2, 3};   // initializers

   for(loop=0; loop<3; loop++)
      cout << obj[loop].get_value() << endl;
 }

