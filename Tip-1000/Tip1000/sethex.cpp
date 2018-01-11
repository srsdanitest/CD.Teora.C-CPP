#include <iostream.h>
#include <iomanip.h>

ostream &sethex(ostream &stream)
 {
   stream.setf(ios::showbase);
   stream.setf(ios::hex);
   return stream;
 }

void main(void)
 {
   cout << 256 << "   " << sethex << 256;
 }
 