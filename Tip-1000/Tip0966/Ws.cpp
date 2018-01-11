#include <iostream.h>

void main(void)
 { 
   char buffer[256];

   cout << "Enter a word with leading blanks" << endl;
   cin >> ws >> buffer;
   cout << "==" << buffer << "==";
 }

