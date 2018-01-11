#include <iostream.h>
#include <string.h>

class SomeClass 
{
 public:
   void show_with_this(void) 
   {
     cout << "Book: " << this->title << endl;
     cout << "Author: " << this->author << endl; 
   };

   void show_without_this(void) 
   {
     cout << "Book: " << title << endl;
     cout << "Author: " << author << endl; 
   };
   
   SomeClass(char *title, char *author) 
   {
     strcpy(SomeClass::title, title);
     strcpy(SomeClass::author, author);
   };

 private:
   char title[256];
   char author[256];
};

void main(void)
 {
   SomeClass book("Jamsa's C/C++ Programmer's Bible", "Jamsa and Klander");

   book.show_with_this();
   book.show_without_this();
 }

