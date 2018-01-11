#include <iostream.h>

void main(void)
 {
   cout << "About to sound the speaker...\n";

   asm 
   {
     MOV AX,0x0200
     MOV DL,7
     INT 0x21
   };
 
   cout << "Done..\n";
 }

