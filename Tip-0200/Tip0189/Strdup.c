#include <stdio.h>
#include <string.h>
 
void main(void)
  {
    char *title;

    if ((title = strdup("Jamsa\'s C/C++ Programmer\'s Bible")))
      printf("Title: %s\n", title);
    else 
      printf("Error duplicating string");
   }
      
     
