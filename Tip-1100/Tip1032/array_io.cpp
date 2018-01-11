#include <iostream.h>
#include <strstrea.h>

void main(void)
 {
   char iostr[80];
   strstream ios(iostr, sizeof(iostr), ios::in | ios::out);
   char str[80];
   int a, b;

   ios << "10 20 testingtesting";
   ios >> a >> b >> str;
   cout << a << "  " << b << "  " << str << endl;
 }

