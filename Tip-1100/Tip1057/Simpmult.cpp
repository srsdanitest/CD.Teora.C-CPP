#include <iostream.h>
#include <string.h>

class Cover 
{
 public:
   Cover(char *title) { strcpy(Cover::title, title); };
 protected:
   char title[256];
};

class Page 
{
 public:
   Page(int lines = 55) { Page::lines = lines; };
 protected:
   int lines;
   char *text;
};

class Book: public Cover, public Page 
{
 public:
   Book(char *author, char *title, float cost): Cover(title), Page(60) 
   {
    strcpy(Book::author, author);
    strcpy(Book::title, title);
    Book::cost = cost; 
   };
   void show_book(void) 
   { 
     cout << title << endl; 
     cout << author << '\t' << cost; 
   };
 private:
   char author[256];
   float cost;
};

void main(void)
 {
   Book text("Jamsa and Klander", "Jamsa's C/C++ Programmer's Bible", 49.95);

   text.show_book();
 }



