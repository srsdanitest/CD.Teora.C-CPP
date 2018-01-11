#include <iostream.h>

class SomeClass 
{
  public:
    SomeClass(int value) { count++; my_data = value; }; 
    SomeClass(int value, int static_value) 
	{
      count = static_value; my_data = value; 
	};
    ~SomeClass(void) { count--; };
    void show_values(void) { cout << my_data << ' ' << count << endl; };
  private:  
    static int count;
    int my_data;
};      

int SomeClass::count;

void main(void)
 {
   SomeClass One(1, 999); 
   One.show_values();   
   
   // Declare another instance
   SomeClass Two(2, 1000);
   Two.show_values();

   // Declare another instance
   SomeClass Three(3);
   Three.show_values();
 }
                           
