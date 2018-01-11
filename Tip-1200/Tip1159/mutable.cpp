#include <iostream.h>

class Alpha 
{
   mutable int count;
   mutable const int* iptr;
public:
   Alpha(void) {count = 0;}
   int func1(int i = 0) const { // Promises not to change const arguments.
      count = i++;  // But count can be changed.
      iptr = &i;
      cout << "i is: " << *iptr << endl;
      return count;
      }
   void show_count(void) { cout << "Count is: " << count << endl;}
};

void main(void)
 {
   Alpha a;

   a.show_count();
   a.func1(10);
   a.show_count();
 }



