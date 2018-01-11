#include <iostream.h>

class sample {
   int value1;
   int value2;
 public:
   sample(int j, int k)      // constructor
   {
     value1 = j;
     value2 = k;
   }   

   int get_value2() {return value2;}
   int get_value1() {return value1;}
 };

void main(void)
 {
   sample obj[3] = {   sample(1,2),
                       sample(3,4),
                       sample(5,6)   };   // initializers
   int loop;

   for(loop=0; loop<3; loop++)
    {
      cout << "Value1, Value 2: ";
      cout << obj[loop].get_value1();
      cout << ", ";
      cout << obj[loop].get_value2() << endl;
    }
 }
