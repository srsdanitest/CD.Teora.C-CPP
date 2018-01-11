#include <iostream.h>
#include <string.h>

struct BookInfo {
  char title[64];
  char publisher[64];
  char author[64];
  float price;
  int pages;
};

class BookStuff {
  public:
    BookStuff(char *title, char *publisher, char *author);
    BookStuff(struct BookInfo);
    void show_book(void) 
	{ cout << "Book: " << title << " by " <<
        author << endl << "Publisher: " << publisher << endl; };
  private:
    char title[64];
    char author[64];
    char publisher[64];
};

BookStuff::BookStuff(char *title, char *publisher, char *author)
 {
   strcpy(BookStuff::title, title);
   strcpy(BookStuff::publisher, publisher);
   strcpy(BookStuff::author, author);
 }

BookStuff::BookStuff(BookInfo book)
 {
   strcpy(BookStuff::title, book.title);
   strcpy(BookStuff::publisher, book.publisher);
   strcpy(BookStuff::author, book.author);
 }

void main(void)
 {
   BookInfo book = {"Rescued by C++, Third Edition", "Jamsa Press", "Jamsa", 29.95, 256 };

   BookStuff big_book("Jamsa's C/C++ Programmer's Bible", "Jamsa Press", 
	   "Jamsa and Klander");
   BookStuff little_book(book);

   big_book.show_book();
   little_book.show_book();
 }
