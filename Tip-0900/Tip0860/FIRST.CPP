#include <iostream.h>
#include <stdlib.h>

void main(int argc, char **argv)
 { 
   char letter;
   int count = 0;
   int line_limit;

   line_limit = atoi(argv[1]);

   while ((letter = cin.get()) != -1)
     {
       cout.put(letter);
       if ((letter == '\n') && (++count == line_limit))
         break;
     }
 }

