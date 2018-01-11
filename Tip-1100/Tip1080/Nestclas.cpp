#include <iostream.h>

class Outer 
{
 public:
   Outer(void) 
   { cout << "Just instantiated an outer\n"; 
     outer_data = 2002; 
   };
   class Inner 
   {
     public:
       Inner(void) 
	   { 
		   cout << "Just instantiated an inner\n"; 
                     inner_data = 1001; 
	   };
       void show_data(void) { cout << "Inner: " << inner_data << endl; };
     private:
       int inner_data;
   } inside_stuff; 
   void show_all_data(void) 
   { 
	   inside_stuff.show_data(); 
       cout << "Outer: " << outer_data << endl; 
   };
 private:
   int outer_data;
};

void main(void)
 {
   Outer my_data;
   my_data.show_all_data();
 }


