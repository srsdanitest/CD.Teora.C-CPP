#include <iostream.h>

enum Days { Monday, Tuesday, Wednesday, Thursday, Friday };

class NeatClass 
{
  public:
    int *lucky_number;
    enum Days lucky_day;
};


void main(void)
 {
   NeatClass wow;
   int lucky = 1500;

   wow.lucky_day = Monday; 
   
   wow.lucky_number = &lucky;

   cout << "My lucky number is " << *(wow.lucky_number) << endl;
   switch (wow.lucky_day) 
   {
     case Monday: cout << "My lucky day is Monday\n";
                  break;

     default: cout << "My lucky day ain't any day but Monday\n";   
   };
 }



