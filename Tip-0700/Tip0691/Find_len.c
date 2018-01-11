#include <stdio.h>

int string_length(char *);

void main(void)
 {
   char *title= "Jamsa\'s C/C++ Programmer\'s Bible";
   char *section = "Tools";

   printf("Length of %s is %d\n", title, string_length(title));
   printf("Length of %s is %d\n", section, string_length(section));
 }

