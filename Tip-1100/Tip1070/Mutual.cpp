#include <iostream.h>
#include <string.h>

class Curly 
{
 public:
   Curly(char *msg) { strcpy(message, msg); };
   void show_message(void) { cout << message << endl; };
   friend class Moe;
   void show_moe(class Moe moe);
 private:
   char message[256];
 };


class Moe 
{
 public:
   Moe(char *msg) { strcpy(message, msg); };
   void show_message(void) { cout << message << endl; };
   friend class Curly;
   void show_curly(class Curly curly);
 private:
   char message[256];
 };


void Curly::show_moe(class Moe moe) { cout << moe.message << endl; };

void Moe::show_curly(class Curly curly) { cout << curly.message << endl; };

void main(void)
 {
   class Moe moe("Nuck, nuck, nuck...");
   class Curly curly("Whoop, whoop, whoop...");
 
   moe.show_message();
   moe.show_curly(curly);
   curly.show_message();
   curly.show_moe(moe);
 }

