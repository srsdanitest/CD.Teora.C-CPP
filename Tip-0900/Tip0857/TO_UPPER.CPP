#include <iostream.h>
#include <ctype.h>

void main(void)
 {
   char letter;

   while ((letter = cin.get()) != -1)
     cout.put(toupper(letter));
 }

