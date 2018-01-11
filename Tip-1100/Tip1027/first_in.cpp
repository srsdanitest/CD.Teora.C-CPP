#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char in_string[] = "10 Hello 0x88 12.23 done";
   istrstream ins(in_string);
   int i;
   char str[80];
   float f;

   ins >> i;
   ins >> str;
   cout << i << " " << str << endl;
   ins >> i;
   ins >> f;
   ins >> str;
   cout << hex << i << " " << f << " " << str;
 }

