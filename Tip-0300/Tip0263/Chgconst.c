#include <stdio.h>
#include <ctype.h>

void no_change(const char *string)
 { 
   char *alias = string;

   while (*alias)
     *alias++ = toupper(*alias);
 }


 void main(void) 
  {
    char title[] = "Jamsa's C/C++ Programmer's Bible";

    no_change(title);

    printf(title);
  }

