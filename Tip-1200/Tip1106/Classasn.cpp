#include <iostream.h>
#include <string.h>


class BookStuff {
  public:
    BookStuff(char *title, char *publisher, char *author);
    void show_book(void) 
	{ 
		cout << "Book: " << title << " by " <<
        author << " Publisher: " << publisher << endl; 
	};
    operator char *();
   
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

BookStuff::operator char *(void)
 {
   char *ptr = new char[256]; 
   
   return(strcpy(ptr, title)); 
 }


void main(void)
 {
   BookStuff big_book("Jamsa's C/C++ Programmer's Bible", "Jamsa Press", 
	   "Jamsa and Klander");
   
   char *title;
   title = big_book;
   cout << "The book's title is " << title << endl;
 }
