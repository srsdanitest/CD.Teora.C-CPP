#include <iostream.h>
#include <string.h>

void main(void)
 {
   char string[256];

   while (cin.getline(string, sizeof(string), '\n'))
     cout << strupr(string) << '\n';
 }

