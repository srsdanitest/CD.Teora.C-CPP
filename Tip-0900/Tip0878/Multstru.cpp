#include <iostream.h>

struct Msg 
{
  char message[256];
  void show_message(void) { cout << message; }
};

void main(void)
 {
   struct Msg book = { "Jamsa's C/C++ Programmer's Bible\n" };
   struct Msg section = { "Getting Started with C++" };

   book.show_message();
   section.show_message();
 }

