#include <iostream.h>

struct Msg 
{
  char message[256];
  void show_message(char *message); 
};

void Msg::show_message(char *message)
 {
   cout << message;
 }


void main(void)
 {
   struct Msg book = { "Jamsa's C/C++ Programmer's Bible" };

   book.show_message(book.message);
 }

