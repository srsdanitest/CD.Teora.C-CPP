#include <iostream.h>
#include <iomanip.h>
#include <string.h>

class Book 
{
  public: 
    char title[256];
    char author[64];
    float price;
    void show_title(void) { cout << title << '\n'; };
    float get_price(void) { return(price); };
    void show_book(void) 
    { 
      show_title(); 
      show_publisher();
    };
    
    void assign_publisher(char *name) { strcpy(publisher, name); };
  private:
    char publisher[256];
    void show_publisher(void) { cout << publisher << '\n'; };
};

void main(void)
 {
   Book bible; 
  
   strcpy(bible.title, "Jamsa's C/C++ Programmer's Bible");
   strcpy(bible.author, "Jamsa and Klander");
   bible.price = 49.95;
   bible.assign_publisher("Jamsa Press");

   bible.show_book();
 }

