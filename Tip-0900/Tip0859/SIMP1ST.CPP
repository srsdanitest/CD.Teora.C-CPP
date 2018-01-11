#include <iostream.h>

void main(void)
 { 
   char letter;
   int count = 0;

   while ((letter = cin.get()) != -1)
     {
       cout.put(letter);
       if ((letter == '\n') && (++count == 10))
         break;
     }
 }

