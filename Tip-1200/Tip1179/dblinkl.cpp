#include <iostream.h>
#include <string.h>
#include <stdlib.h>

class list_object 
{
 public:
   char info;
   list_object *next;
   list_object *previous;
   list_object(void) {
      info = 0;
      next = NULL;
      previous = NULL;
    }
   list_object *getnext(void) {return next;}
   list_object *getprevious(void) {return previous;}
   void getinfo(char &c) { c = info;}
   void change(char c) {info = c;}
   friend ostream &operator<<(ostream &stream, list_object o)
    {
      stream << o.info << endl;
      return stream;
    }
   friend ostream &operator<<(ostream &stream, list_object *o)
    {
      stream << o->info << endl;
      return stream;
    }
   friend istream &operator>>(istream &stream, list_object &o)
    {
      cout << "Enter information: " << endl;
      stream >> o.info;
      return stream;
    }
 };