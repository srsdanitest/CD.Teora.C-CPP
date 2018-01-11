#include <iostream.h>

class SomeClass 
{
  public:
    static int count;
    SomeClass(int value) 
    { 
      count++; 
      my_data = value;
    }; 
    ~SomeClass(void) 
    { 
      count--;
    };
    int my_data;
};      

int SomeClass::count;

void main(void)
 {
   SomeClass One(1); 
   cout << "One: " << One.my_data << ' ' << One.count << endl ;
   
   // Declare another instance
   SomeClass Two(2);
   cout << "Two: " << Two.my_data << ' ' << Two.count << endl ;
   
   // Declare another instance
   SomeClass Three(3);
   cout << "Three: " << Three.my_data << ' ' << Three.count << endl ;
 }
                           
