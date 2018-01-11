#include <iostream.h>

struct Msg 
{
  char message[256];
  void show_message(void) { cout << message; }
};

void main(void)
 {
   struct Msg book = { "Jamsa's C/C++ Programmer's Bible" };

   book.show_message();
 }

