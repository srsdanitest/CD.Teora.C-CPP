#include <iostream.h>
#include <iomanip.h>

ostream &indent(ostream &stream, int length)
 {
   register int i;

   for(i=0; i<length; i++)
      cout << " ";
   return stream;
 }

omanip<int> indent(int length)
 {
   return omanip<int>(indent, length);
 }

void main(void)
 {
   cout << indent(10) << "This is a test." << endl;
   cout << indent(20) << "of the new indent manipulator." << endl;
   cout << indent(5) << "It works!" << endl;
 }


