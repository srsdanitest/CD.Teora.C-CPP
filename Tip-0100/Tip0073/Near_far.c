#include <stdio.h>

void main(void)
 {
   char *near_title = "Jamsa\'s C/C++ Programmer\'s Bible";
   char far *far_title = "Jamsa\'s C/C++ Programmer\'s Bible";

   printf("The book\'s title: %Ns\n", near_title);
   printf("The book\'s title: %Fs\n", far_title);
 }
