#include <iostream.h>
#include <iomanip.h>
#include <string.h>

class Book 
{
  public: 
    void show_title(void) { cout << title << '\n'; };
    void show_book(void) { show_title(); show_publisher(); };
    void assign_members(char *, char *, char *, float);
  private:
    char title[256];
    char author[64];
    float price;
    char publisher[256];
    void show_publisher(void) { cout << publisher << '\n'; };
};


void Book::assign_members(char *title, char *author, char *publisher,
    float price)
 {
   strcpy(Book::title, title);
   strcpy(Book::author, author);
   strcpy(Book::publisher, publisher);
   Book::price = price;
 }


void main(void)
 {
   Book Library[4];

   Library[0].assign_members("Jamsa's C/C++ Programmer's Bible", "Jamsa and Klander", 
	   "Jamsa Press", 49.95);
   Library[1].assign_members("Hacker Proof", "Klander", "Jamsa Press", 54.95); 
   Library[2].assign_members("ActiveX Programmer's Library", "Lalani and Chandak",
        "Jamsa Press", 49.95);
   Library[3].assign_members("Rescued by C++, Third Edition", "Jamsa", 
        "Jamsa Press", 24.95);
 
   for (int i = 0; i < 4; i++)
     Library[i].show_book();
 }

