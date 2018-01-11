#include <iostream.h>

struct book 
{
  char author[64];
  char title[64];
  float price;
};

book library[3] = {
  {"Jamsa and Klander", "Jamsa's C/C++ Programmer's Bible", 49.95},
  {"Klander", "Hacker Proof", 54.95},
  {"Jamsa and Klander", "1001 Visual Basic Programmer's Tips", 54.95}};

book& get_book(int i)
 {
   if ((i >= 0) && (i < 3))
     return(library[i]);
   else
     return(library[0]);
 }

void main(void)
 {
   cout << "About to get book 0\n";
   book& this_book = get_book(0);
   cout << this_book.author << ' ' << this_book.title;
   cout << ' ' << this_book.price;
 }

