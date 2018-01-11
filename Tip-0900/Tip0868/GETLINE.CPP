#include <iostream.h>

void main(void)
 {
   char string[256];

   cout << "Type in your full name and press Enter\n";
   cin.getline(string, sizeof(string), '\n');
   cout << string;
 }


