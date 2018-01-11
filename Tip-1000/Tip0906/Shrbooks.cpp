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
    void show_book(void); 
    void assign_publisher(char *name) { strcpy(publisher, name); };
  private:
    char publisher[256];
    void show_publisher(void) { cout << publisher << '\n'; };
};

void Book::show_book(void) 
  { 
    show_title(); 
    show_publisher(); 
  };
  
void main(void)
 {
   Book tips, diary; 
  
   strcpy(tips.title, "Jamsa's C/C++ Programmer's Bible");
   strcpy(tips.author, "Jamsa and Klander");
   tips.price = 49.95;
   tips.assign_publisher("Jamsa Press");
   
   strcpy(diary.title, "All My Secrets...");
   strcpy(diary.author, "Kris Jamsa");
   diary.price = 9.95;
   diary.assign_publisher("None");

   tips.show_book();
   diary.show_book();
 
 }

