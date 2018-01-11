#include <iostream.h>
#include <iomanip.h>
#include <string.h>

class Book 
{
  public: 
    void show_title(void) { cout << title << '\n'; };
    void show_book(void) 
    { 
      show_title();
      show_publisher();
    };
    Book(char *title, char *author, char *publisher, float price);
    ~Book(void) { cout << "Destroying the entry for " << title << endl; };
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

void main(void)
 {
   Book *Library[4];
   int i = 0;

   Library[0] = new Book("Jamsa's C/C++ Programmer's Bible", "Jamsa and Klander",
     "Jamsa Press", 49.95);
   Library[1] = new Book("Hacker Proof", "Klander", "Jamsa Press", 54.95);
   Library[2] = new Book("ActiveX Programmer's Library", "Suleiman and Lalani",
     "Jamsa Press", 49.95);
   Library[3] = new Book("Rescued by C++, Third Edition", "Jamsa", 
	   "Jamsa Press", 24.95);

   for (i = 0; i < 4; i++)
     Library[i]->show_book();
   for (i = 0; i < 4; i++)
     delete Library[i];
 }

