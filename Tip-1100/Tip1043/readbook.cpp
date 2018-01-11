#include <iostream.h>
#include <string.h>

class Reader;							//Forward declaration

class Book 
{
  public:
    Book(char *title) { strcpy(Book::title, title); } ;
    void show_book(void) { cout << title; };
    friend Reader;
  private:
    char title[64];
};

class Reader 
{
  public:
    Reader(char *name) { strcpy(Reader::name, name); };
    void show_reader(class Book book) 
    { 
      cout << "Reader: " << name << ' ' << "Book: " << book.title; 
    };
  private:
    char name[64];
};

void main(void)
 {
    Reader reader("Kris Jamsa");
    Book favorite_book("Compiler Internals");

    reader.show_reader(favorite_book);
 }
