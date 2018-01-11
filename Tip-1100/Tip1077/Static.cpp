#include <iostream.h>

class SomeClass 
{
  public:  
    SomeClass(int value) { some_value = value; };
    void show_data(void) { cout << data << ' ' << some_value << endl; };
    static void set_data(int value) { data = value; };
  private:
    static int data;
    int some_value;
};

int SomeClass::data;

void main(void)
 {
   SomeClass my_class(1001);
   my_class.set_data(5005);
   my_class.show_data();
 }




