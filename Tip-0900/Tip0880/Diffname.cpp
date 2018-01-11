#include <iostream.h>
#include <string.h>

struct Msg 
{
  char message[256];
  void show_message(void); 
};


struct UpperMsg 
{
   char message[256];
   void show_message(void); 
};


void Msg::show_message(void)
 {
   cout << message;
 }

void UpperMsg::show_message(void)
 {
   cout << strupr(message);
 }

void main(void)
 {
   Msg book = { "Jamsa's C/C++ Programmer's Bible\n" };
   UpperMsg book_upr = { "C/C++ PROGRAMMER'S BIBLE\n" };

   book.show_message();
   book_upr.show_message();
 }

