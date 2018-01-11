#include <iostream.h>
#include <iomanip.h>
#include <string.h>
#include <stdlib.h>

class Book 
{
  public: 
    char *title;
    char *author;
    float price;
    Book(char *title, char *author, char *publisher, float price);
    void show_title(void) { cout << title << '\n'; };
    float get_price(void) { return(price); };
    void show_book(void) 
    { 
      show_title(); 
      show_publisher(); 
    };
    void assign_publisher(char *name) { strcpy(publisher, name); };
  private:
    char *publisher;
    void show_publisher(void) { cout << publisher << '\n'; };
};

Book::Book(char *title, char *author, char *publisher, float price)
 {
   if ((Book::title = new char[256]) == 0)
     {
       cerr << "Error allocating memory\n";
       exit(0);
     }

   if ((Book::author = new char[64]) == 0)
     {
       cerr << "Error allocating memory\n";
       exit(0);
     }

   if ((Book::publisher = new char[128]) == 0)
     {
       cerr << "Error allocating memory\n";
       exit(0);
     }

   strcpy(Book::title, title);
   strcpy(Book::author, author);
   strcpy(Book::publisher, publisher);
   Book::price = price;
 }

void main(void)
 {
   Book tips("Jamsa’s C/C++ Programmer’s Bible", "Jamsa and Klander", "Jamsa Press",
      49.95);
   Book diary("All My Secrets...", "Kris Jamsa", "None", 9.95);

   tips.show_book();
   diary.show_book();
 }
