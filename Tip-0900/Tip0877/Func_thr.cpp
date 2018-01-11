#include <iostream.h>

struct Msg 
{
  char first[256];
  void show_title(int value) 
   { 
     cout << first << value << " C/C++ Tips"; 
   }
};

void main(void)
 {
   struct Msg book = { "This book has " };

   book.show_title(1500);
 }

