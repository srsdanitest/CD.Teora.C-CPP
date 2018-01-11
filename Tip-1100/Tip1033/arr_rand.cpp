#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char name[]="Jamsa's C/C++ Programmer's Bible";
   char iostr[80];
   strstream ios(iostr, sizeof(iostr), ios::in | ios::out);
   char ch;

   ios << name;
   ios.seekg(7, ios::beg);
   ios >> ch;
   cout << "Name: " << name << endl;
   cout << "Character at position 8: " << ch;
 }

