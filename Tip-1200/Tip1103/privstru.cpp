#include <iostream.h>
#include <string.h>

struct MyBook {
  char title[64];  // Public by default
  void show_book(void) 
    {
      cout << "Book: " << title << " Price: $" << price ;  
    };
  
  void set_price(float amount) { price = amount; };
  void assign_title(char *name) { strcpy(title, name); };
  private:
    float price;
};

void main(void)
 {
   MyBook book; 

   book.assign_title("Jamsa's C/C++ Programmer's Bible");
   book.set_price(49.95);
   book.show_book();
 }

