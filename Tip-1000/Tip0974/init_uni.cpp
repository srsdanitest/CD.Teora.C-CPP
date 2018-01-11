#include <iostream.h>

class sample 
{
   int value;
 public:
   sample() {value = 0;};            // uninitialized constructor
   sample(int j) {value = j;}        // constructor
   int get_value() {return value;}
 };

void main(void)
 {
   int loop;
   sample obj1[3] = {1, 2, 3};
   sample obj2[32];

   cout << "Entering first loop: " << endl;
   for(loop=0; loop<3; loop++)
     cout << obj1[loop].get_value() << endl;
   cout << "Entering second loop: " << endl;
   for(loop=0; loop<32; loop++)
     cout << obj2[loop].get_value() << ", ";
   cout << endl;
 }
