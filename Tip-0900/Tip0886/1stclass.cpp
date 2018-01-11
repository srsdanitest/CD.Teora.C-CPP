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
};

void main(void)
 {
   Book tips; 
  
   strcpy(tips.title, "Jamsa's C/C++ Programmer's Bible");
   strcpy(tips.author, "Jamsa and Klander");
   tips.price = 49.95;

   tips.show_title();
   cout << "The book's price is " << setprecision(2) << 
     tips.get_price();
 }

