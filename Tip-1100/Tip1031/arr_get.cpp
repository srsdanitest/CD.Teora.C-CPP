#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char str[] ="abcdefghijklmnop";
   istrstream ins(str);
   char ch;

   while(!ins.eof())
    {
      ins.get(ch);
      cout << ch << " ";
    }
 }

