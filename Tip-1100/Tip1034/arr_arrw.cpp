#include <iostream.h>
#include <strstrea.h>

ostream &ra(ostream &stream)
 {
   stream << "-------->";
   return stream;
 }

ostream &la(ostream &stream)
 {
   stream << "<--------";
   return stream;
 }

void main(void)
 {
   char str[80];
   ostrstream outs(str, sizeof(str));

   outs << ra << "Look at this number: ";
   outs << 100000 << la << ends;
   cout << "  " << str << endl;
 }

