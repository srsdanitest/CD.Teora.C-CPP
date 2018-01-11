#include <iostream.h>
#include <iomanip.h>
#include <string.h>

class Book 
{
  public: 
    char title[256];
    char author[64];
    float price;
    void show_title(void); 
    float get_price(void); 
    void show_book(void); 
    void assign_publisher(char *name); 
  private:
    char publisher[256];
    void show_publisher(void); 
};

void Book::show_title(void) 
  { cout << title << '\n'; };

float Book::get_price(void) 
  { return(price); };
    
void Book::show_book(void) 
  { 
  show_title(); 
  show_publisher();
  };

void Book::assign_publisher(char *name) 
  { strcpy(publisher, name); };

void Book::show_publisher(void) 
  { cout << publisher << '\n'; };

void main(void)
 {
   Book tips; 
  
   strcpy(tips.title, "Jamsa's C/C++ Programmer's Bible");
   strcpy(tips.author, "Jamsa and Klander");
   tips.price = 49.95;
   tips.assign_publisher("Jamsa Press");

   tips.show_book();
 }

