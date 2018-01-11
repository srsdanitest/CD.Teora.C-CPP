#include <iostream.h>
#include <iomanip.h>
#include <string.h>
#include <stdlib.h>

class Book 
{
  public: 
    Book(char *title, char *author, char *publisher, float price);
    Book(void);
    void show_title(void) { cout << title << '\n'; };
    float get_price(void) { return(price); };
    void show_book(void) 
    { 
      show_title(); 
      show_publisher();
    };
  private:
    char title[256];
    char author[64];
    float price;
    char publisher[256];
    void show_publisher(void) { cout << publisher << '\n'; };
};

Book::Book(char *title, char *author, char *publisher, float price)
 {
   strcpy(Book::title, title);
   strcpy(Book::author, author);
   strcpy(Book::publisher, publisher);
   Book::price = price;
 }

Book::Book(void)
 {
   cerr << "You must specify initial values for Book instance\n";
   exit(1);
 }
void main(void)
 {
   Book tips("Jamsa's C/C++ Programmer's Bible", "Jamsa and Klander", 
	   "Jamsa Press", 49.95);
   Book diary;

   tips.show_book();
   diary.show_book();
 }

