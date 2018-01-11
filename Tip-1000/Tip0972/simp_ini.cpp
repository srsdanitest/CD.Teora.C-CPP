#include <iostream.h>

class sample 
{
   int value;
 public:
   void set_value(int j) {value = j;}
   int get_value() {return value;}
 };

void main(void)
 {
   sample obj[3];
   int loop;

   for(loop=0; loop<3; loop++)
      obj[loop].set_value(loop+1);
   for(loop=0; loop<3; loop++)
      cout << obj[loop].get_value() << endl;
 }
 
