#include <stdio.h>

void no_change(const char *string)
 { 
   while (*string)
     *string++ = toupper(*string);
 }


 void main(void) 
  {
    char title[] = "Jamsa\'s C/C++ Programmer\'s Bible";

    no_change(title);

    printf(title);
  }

